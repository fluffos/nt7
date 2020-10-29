inherit ROOM;
void create()
{
        set("short", "河洛镖局");
        set("long", @LONG
一座建构宏伟的宅第之前，左右两座石坛中各竖一根两丈来高的
旗杆，旗杆顶飘扬青旗。右首旗上黄色丝线绣著一头张牙舞爪、神态
威猛的金龙，旗子随风招展，显得金龙更奕奕若生。左首旗上绣著「
河洛镖局」四个黑字，银钩铁划，刚劲非凡。进门处两排长凳，分坐
著八名身着劲装的汉子，个个腰板笔挺，显出一股英悍之气。
LONG );
        set("exits", ([
                "north" : "/d/changan/qixiang5",
                "south" : "/d/changan/biaoju-dayuan",
        ]));
        set("objects", ([
                "/d/changan/npc/biaoshi" : 1,
                "/d/changan/npc/tang" : 2,
        ]) );

        set("coor/x", -10700);
	set("coor/y", 1960);
	set("coor/z", 0);
	setup();
}