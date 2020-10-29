inherit ROOM;
void create()
{
        set("short", "柳绿山庄");
        set("long",
"此时天色已暗，庄门裂开，只见这座破旧的庄院深邃阔大，不知至何\n"
"处终止。前面一条长长的甬道，已被白雪所覆盖，一路通往庄院。\n"
);
        set("no_magic", "1");

        set("exits", ([ /* sizeof() == 2 */
          "north" : __DIR__"yongdao2",
          "south" : __DIR__"gate",
        ]));
        setup();
}
