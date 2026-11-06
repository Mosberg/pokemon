#!/usr/bin/env python3
"""
web_server.py - Embedded zero-dependency HTTP server and REST API for
Pokémon Confluence Configuration Studio.
"""

import json
import os
import shutil
import subprocess
import sys
import urllib.parse
from http.server import BaseHTTPRequestHandler, HTTPServer
from pathlib import Path

from config_engine import PRESETS, ConfigEngine

# Add script directory to sys.path
SCRIPT_DIR = Path(__file__).resolve().parent
if str(SCRIPT_DIR) not in sys.path:
    sys.path.insert(0, str(SCRIPT_DIR))


WORKSPACE_DIR = Path("/home/mosberg/wsl_projects/pokemon").resolve()
ROM_DIR = WORKSPACE_DIR / "pokeconfluence"
STATIC_DIR = SCRIPT_DIR / "static"


class ConfigApiHandler(BaseHTTPRequestHandler):
    engine = ConfigEngine()

    def _set_headers(self, status=200, content_type="application/json"):
        self.send_response(status)
        self.send_header("Content-Type", content_type)
        self.send_header("Access-Control-Allow-Origin", "*")
        self.send_header("Access-Control-Allow-Methods", "GET, POST, OPTIONS")
        self.send_header("Access-Control-Allow-Headers", "Content-Type")
        self.send_header("Cache-Control", "no-cache, no-store, must-revalidate")
        self.end_headers()

    def do_OPTIONS(self):
        self._set_headers(204)

    def log_message(self, format, *args):
        if self.path.startswith("/api/"):
            super().log_message(format, *args)

    def do_GET(self):
        parsed = urllib.parse.urlparse(self.path)
        path = parsed.path

        if path == "/" or path == "/index.html":
            html_file = STATIC_DIR / "index.html"
            if html_file.exists():
                with open(html_file, "rb") as f:
                    content = f.read()
                self._set_headers(200, "text/html; charset=utf-8")
                self.wfile.write(content)
            else:
                self._set_headers(404, "text/plain")
                self.wfile.write(b"index.html not found")
            return

        if path == "/api/files":
            files = self.engine.list_files()
            self._set_headers(200)
            self.wfile.write(json.dumps({"success": True, "files": files}).encode("utf-8"))
            return

        if path.startswith("/api/config/"):
            filename = path.replace("/api/config/", "")
            cfgs = self.engine.parse_file(filename)
            self._set_headers(200)
            self.wfile.write(json.dumps({"success": True, "filename": filename, "configs": cfgs}).encode("utf-8"))
            return

        if path == "/api/all":
            all_cfgs = self.engine.get_all_configs()
            files = self.engine.list_files()
            self._set_headers(200)
            self.wfile.write(
                json.dumps({"success": True, "files": files, "configs": all_cfgs, "presets": PRESETS}).encode("utf-8")
            )
            return

        if path == "/api/presets":
            self._set_headers(200)
            self.wfile.write(json.dumps({"success": True, "presets": PRESETS}).encode("utf-8"))
            return

        if path == "/api/backups":
            backups = self.engine.list_backups()
            self._set_headers(200)
            self.wfile.write(json.dumps({"success": True, "backups": backups}).encode("utf-8"))
            return

        self._set_headers(404)
        self.wfile.write(json.dumps({"error": "Not found"}).encode("utf-8"))

    def do_POST(self):
        parsed = urllib.parse.urlparse(self.path)
        path = parsed.path

        content_length = int(self.headers.get("Content-Length", 0))
        body = self.rfile.read(content_length).decode("utf-8") if content_length > 0 else "{}"
        try:
            data = json.loads(body)
        except Exception:
            data = {}

        if path == "/api/diff":
            updates = data.get("updates", {})
            diffs = self.engine.compute_diff(updates)
            self._set_headers(200)
            self.wfile.write(json.dumps({"success": True, "diffs": diffs}).encode("utf-8"))
            return

        if path == "/api/save":
            updates = data.get("updates", {})
            result = self.engine.save_changes(updates)
            self._set_headers(200)
            self.wfile.write(json.dumps(result).encode("utf-8"))
            return

        if path == "/api/restore":
            backup_id = data.get("backup_id", "")
            result = self.engine.restore_backup(backup_id)
            self._set_headers(200)
            self.wfile.write(json.dumps(result).encode("utf-8"))
            return

        if path == "/api/build":
            try:
                cmd = ["make", "-C", str(ROM_DIR), f"-j{os.cpu_count() or 4}"]
                proc = subprocess.run(cmd, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True, timeout=180)
                output = proc.stdout
                success = proc.returncode == 0
                self._set_headers(200)
                self.wfile.write(
                    json.dumps({"success": success, "returncode": proc.returncode, "output": output}).encode("utf-8")
                )
            except subprocess.TimeoutExpired:
                self._set_headers(200)
                self.wfile.write(
                    json.dumps({"success": False, "error": "Build timed out after 180 seconds"}).encode("utf-8")
                )
            except Exception as e:
                self._set_headers(500)
                self.wfile.write(json.dumps({"success": False, "error": str(e)}).encode("utf-8"))
            return

        self._set_headers(404)
        self.wfile.write(json.dumps({"error": "Not found"}).encode("utf-8"))


def find_available_port(start_port=8088, max_attempts=20):
    import socket

    for port in range(start_port, start_port + max_attempts):
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
            if s.connect_ex(("127.0.0.1", port)) != 0:
                return port
    return start_port


def open_browser(url):
    """Attempt to open browser across WSL2, Linux, and Windows hosts."""
    import webbrowser

    if shutil.which("wslview"):
        try:
            subprocess.Popen(["wslview", url], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
            return
        except Exception:
            pass

    if shutil.which("cmd.exe"):
        try:
            subprocess.Popen(["cmd.exe", "/c", "start", url], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
            return
        except Exception:
            pass

    try:
        webbrowser.open(url)
    except Exception:
        pass


def run_server(port=None, launch_browser=True):
    if port is None:
        port = find_available_port(8088)

    server = HTTPServer(("0.0.0.0", port), ConfigApiHandler)
    url = f"http://localhost:{port}"
    print("===========================================================")
    print(" Pokémon Confluence Configuration Studio v2.5")
    print(f" Web GUI running at: {url}")
    print(f" Serving configs from: {ROM_DIR / 'include/config'}")
    print(" Press Ctrl+C to stop the server")
    print("===========================================================")

    if launch_browser:
        open_browser(url)

    try:
        server.serve_forever()
    except KeyboardInterrupt:
        print("\nStopping Configuration Studio server...")
        server.server_close()


if __name__ == "__main__":
    import argparse

    parser = argparse.ArgumentParser(description="Pokémon Confluence Configuration Studio Web GUI")
    parser.add_argument("--port", type=int, default=None, help="Port to run on (default: auto 8088+)")
    parser.add_argument("--no-browser", action="store_true", help="Don't automatically open browser")
    args = parser.parse_args()

    run_server(port=args.port, launch_browser=not args.no_browser)
