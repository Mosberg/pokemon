RedsHouse1F_Johto_MapScripts::
	.byte 0

RedsHouse1F_Johto_RedsMom_Entry::
	lockall
	goto RedsHouse1F_Johto_RedsMom

RedsHouse1F_Johto_RedsHouse1FBookshelf_Entry::
	lockall
	goto RedsHouse1F_Johto_RedsHouse1FBookshelf

RedsHouse1F_Johto_RedsHouse1FTV_Entry::
	lockall
	goto RedsHouse1F_Johto_RedsHouse1FTV


RedsHouse1F_Johto_RedsMom:
	faceplayer
	goto_if_set FLAG_JOHTO_MET_REDS_MOM, RedsHouse1F_Johto_RedsMom_MetAlready
	message RedsHouse1F_Johto_RedsMomText1
	waitmessage
	waitbuttonpress
	closemessage
	setflag FLAG_JOHTO_MET_REDS_MOM
	releaseall
	end

RedsHouse1F_Johto_RedsMom_MetAlready:
	message RedsHouse1F_Johto_RedsMomText2
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

RedsHouse1F_Johto_RedsHouse1FTV:
	message RedsHouse1F_Johto_RedsHouse1FTVText
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

RedsHouse1F_Johto_RedsHouse1FBookshelf:
	goto Johto_Std_PictureBookshelfScript

RedsHouse1F_Johto_RedsMomText1:
	.string "Hi!"
	.string "\pRED's been away\n"
	.string "for a long time."
	.string "\pHe hasn't called\n"
	.string "either, so I have"
	.string "\pno idea where he\n"
	.string "is or what he's\l"
	.string "been doing."
	.string "\pThey say that no\n"
	.string "word is proof that"
	.string "\phe's doing fine,\n"
	.string "but I do worry\l"
	.string "about him.$"

RedsHouse1F_Johto_RedsMomText2:
	.string "I worry about RED\n"
	.string "getting hurt or"
	.string "\psick, but he's a\n"
	.string "boy. I'm proud"
	.string "\pthat he is doing\n"
	.string "what he wants to"
	.string "\pdo.$"

RedsHouse1F_Johto_RedsHouse1FTVText:
	.string "They have programs\n"
	.string "that aren't shown\l"
	.string "in JOHTO…$"
