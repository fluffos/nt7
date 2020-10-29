// This is a room made by wsl.
inherit ROOM;
void create()
{
    set("short", "石道");
        set("long", @LONG
石道两旁的石兽由原本代表帝皇的狮子，变成了象徵疆域广阔的
骆驼，然後是四灵之首的麒麟，再是喻意武功昌盛、南征北讨的战马，
跟着是羊头牛尾，顶生独角的獬兽。
LONG );
    set("exits", ([
       "north" :__DIR__"shidao1",
       "south" :__DIR__"shendao",
]));
    setup();
    replace_program(ROOM);
}