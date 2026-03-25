const cards = document.querySelectorAll(".project-card");

cards.forEach(card=>{
card.addEventListener("mouseenter",()=>{
card.style.background="#334155";
});

card.addEventListener("mouseleave",()=>{
card.style.background="#1e293b";
});
});