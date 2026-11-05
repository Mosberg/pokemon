document.addEventListener("DOMContentLoaded", () => {
  // 1. Interactive Spotlight & 3D Tilt on Region Cards
  const cards = document.querySelectorAll(".region-card");
  const prefersReducedMotion = window.matchMedia("(prefers-reduced-motion: reduce)").matches;

  cards.forEach((card) => {
    let rafId = null;

    card.addEventListener("mousemove", (e) => {
      if (rafId) cancelAnimationFrame(rafId);

      rafId = requestAnimationFrame(() => {
        const rect = card.getBoundingClientRect();
        const x = e.clientX - rect.left;
        const y = e.clientY - rect.top;

        card.style.setProperty("--mouse-x", `${x}px`);
        card.style.setProperty("--mouse-y", `${y}px`);

        if (!prefersReducedMotion) {
          const centerX = rect.width / 2;
          const centerY = rect.height / 2;
          const rotateX = ((y - centerY) / centerY) * -3;
          const rotateY = ((x - centerX) / centerX) * 3;
          card.style.transform = `perspective(1000px) rotateX(${rotateX.toFixed(2)}deg) rotateY(${rotateY.toFixed(2)}deg) translateY(-4px)`;
        }
      });
    });

    card.addEventListener("mouseleave", () => {
      if (rafId) cancelAnimationFrame(rafId);
      card.style.setProperty("--mouse-x", `-500px`);
      card.style.setProperty("--mouse-y", `-500px`);
      if (!prefersReducedMotion) {
        card.style.transform = "";
      }
    });
  });

  // 2. Accessible Native Modal Handling (<dialog>)
  const modal = document.getElementById("info-modal");
  const openModalBtn = document.getElementById("open-terminal-btn");
  const inspectLimitsBtn = document.getElementById("inspect-limits-btn");
  const closeModalBtn = document.getElementById("modal-close-btn");

  const openDialog = () => {
    if (modal && typeof modal.showModal === "function") {
      modal.showModal();
    }
  };

  const closeDialog = () => {
    if (modal && typeof modal.close === "function") {
      modal.close();
    }
  };

  if (openModalBtn) openModalBtn.addEventListener("click", openDialog);
  if (inspectLimitsBtn) inspectLimitsBtn.addEventListener("click", openDialog);
  if (closeModalBtn) closeModalBtn.addEventListener("click", closeDialog);

  // Close dialog on backdrop click
  if (modal) {
    modal.addEventListener("click", (e) => {
      const dialogDimensions = modal.getBoundingClientRect();
      if (
        e.clientX < dialogDimensions.left ||
        e.clientX > dialogDimensions.right ||
        e.clientY < dialogDimensions.top ||
        e.clientY > dialogDimensions.bottom
      ) {
        closeDialog();
      }
    });
  }

  // 3. Command Clipboard Copy Helper
  const copyBtn = document.getElementById("copy-cmd-btn");
  if (copyBtn) {
    copyBtn.addEventListener("click", async () => {
      const commandText = "scripts/build.sh";
      try {
        await navigator.clipboard.writeText(commandText);
        const originalText = copyBtn.textContent;
        copyBtn.textContent = "Copied!";
        copyBtn.style.color = "#10b981";
        setTimeout(() => {
          copyBtn.textContent = originalText;
          copyBtn.style.color = "";
        }, 2000);
      } catch (err) {
        console.error("Clipboard access failed:", err);
      }
    });
  }
});