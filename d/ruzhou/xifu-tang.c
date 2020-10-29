// Room: /ruzhou/xifu-tang.c //举办婚宴所在
// llm 99/07/09

inherit ROOM;
void create()
{
        set("short", "喜福堂");
        set("long", @LONG
这里是迎宾楼的二楼，宽敞地可以摆下三十多张八仙桌，正中挂
着大大的红色喜字，由于常常有人在此举办婚宴，这里的红烛也就长
明，地上铺着厚厚的大红地毯，一派喜气洋洋的景象。你站在楼上眺
望，可看见碧波湖水，崇山峻岭。
LONG
);
        set("exits", ([
                "down" : __DIR__"yingbin-lou1",
        ]));

	set("coor/x", -6770);
	set("coor/y", 1850);
	set("coor/z", 10);
	setup();
   replace_program(ROOM);
}