LavenderMart_Johto_MapScripts::
	.byte 0

LavenderMart_Johto_LavenderMartClerkScript_Entry::
	lockall
	goto LavenderMart_Johto_LavenderMartClerkScript

LavenderMart_Johto_LavenderMartPokefanMScript_Entry::
	lockall
	goto LavenderMart_Johto_LavenderMartPokefanMScript

LavenderMart_Johto_LavenderMartRockerScript_Entry::
	lockall
	goto LavenderMart_Johto_LavenderMartRockerScript


LavenderMart_Johto_LavenderMartClerkScript:
	pokemart Johto_Mart_LAVENDER
	closemessage
	releaseall
	end

LavenderMart_Johto_LavenderMartPokefanMScript:
	faceplayer
	message LavenderMart_Johto_LavenderMartPokefanMText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

LavenderMart_Johto_LavenderMartRockerScript:
	faceplayer
	message LavenderMart_Johto_LavenderMartRockerText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

LavenderMart_Johto_LavenderMartPokefanMText:
	.string "REPEL is a neces-\n"
	.string "sity if you are"
	.string "\pgoing to explore a\n"
	.string "cave."
	.string "\pEven though I like\n"
	.string "exploring, I still"
	.string "\phaven't made it to\n"
	.string "all the caves.$"

LavenderMart_Johto_LavenderMartRockerText:
	.string "I heard about a\n"
	.string "craftsman who"
	.string "\pmakes custom BALLS\n"
	.string "in the JOHTO town"
	.string "\pof AZALEA. I wish\n"
	.string "I had some.$"
