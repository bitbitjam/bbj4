
var texto =[
"CONGRATULATIONSA",
"YOU SOLD YOUR OLD",
"HELICOPTER AND",
"BOUGHT A NEW ONEA",
"YOUR BUSINESS IS",
"A SUCCESSA BUT",
"THATS NOT AN",
"HISTORY FOR THIS",
"GAME",
"THANKS FOR PLAYING",
];
//65 base
for (var j=0; j<texto.length; j++) {
	var out = "";
	for(var i=0; i<texto[j].length; i++) {
		out +=  (texto[j].charCodeAt(i)) +"	"; 
	}
	console.log(out);
}
