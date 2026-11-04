document.addEventListener("DOMContentLoaded", () => {
  // Smooth scroll routing for in-page anchors
  document.querySelectorAll('a[href^="#"]').forEach((anchor) => {
    anchor.addEventListener("click", function (e) {
      const targetId = this.getAttribute("href");
      if (targetId === "#" || targetId === "") return;

      const targetElement = document.querySelector(targetId);
      if (targetElement) {
        e.preventDefault();
        targetElement.scrollIntoView({
          behavior: "smooth",
          block: "start",
        });
      }
    });
  });

  // CTA button modal/status alert
  const ctaButton = document.getElementById("cta-button");
  if (ctaButton) {
    ctaButton.addEventListener("click", (e) => {
      e.preventDefault();
      alert(
        "The Triad Convergence has begun. Connect via the regional terminal to board the transit network!",
      );
    });
  }

  // Card interactive tilt highlight
  const cards = document.querySelectorAll(".region-card");
  cards.forEach((card) => {
    card.addEventListener("mousemove", (e) => {
      const rect = card.getBoundingClientRect();
      const x = e.clientX - rect.left;
      const y = e.clientY - rect.top;

      card.style.setProperty("--mouse-x", `${x}px`);
      card.style.setProperty("--mouse-y", `${y}px`);
    });
  });
});
