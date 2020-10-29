// Room: liupeng.c

inherit ROOM;

void create()
{
        set("short", "牛棚");
        set("long", @LONG
这是一个小小的茅屋，茅屋前是一片黄澄澄的耕地，一个
牧童正站在茅屋前傻傻的发愣，一面愁容，还喃喃道：“完了，
，完了.....!”
LONG
        );
        set("exits", ([ /* sizeof() == 1 */
  "southwest" : __DIR__"maowu",
]));
        set("no_clean_up", 0);

        setup();
        replace_program(ROOM);
}
