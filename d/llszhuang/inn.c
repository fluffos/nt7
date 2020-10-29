inherit ROOM;
void create()
{
        set("short", "枫林小栈");
        set("long",
"这是枫林渡口旁边的一个小酒家，破烂的酒旗在北风中飞舞。北面的\n"
"路通往曾经声名显赫一时的绿柳山庄。自从绿柳山庄的凶讯传扬开去之后，\n"
"这里就变得非常冷清了。只有要去绿柳山庄探明究竟的人才会在这里喝点\n"
"酒，壮一壮胆，攒足精神。\n"
);

        set("exits", ([ /* sizeof() == 2 */
          "north" : __DIR__"dukou",
          "southeast" : __DIR__"road2",
        ]));
        set("objects", ([
           // "/d/city/npc/xiaoer2" : 1,
        ]));
        setup();
}
