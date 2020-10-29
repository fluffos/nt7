inherit ROOM;

void create()
{
        set("short", "观音堂");
        set("long", @LONG
观音堂高踞坡岗近临危崖，环境幽静，四周树木蓊郁，悦目赏心。
传说入山于此，解脱尘凡；出山于此，解脱险阻，又故名解脱庵。进
山的人在此焚香洗心，入山方可化险为夷步步平安。这里东下可达伏
虎寺，西上行约二里可到归云阁。
LONG );
        set("exits", ([
                "eastdown"  : __DIR__"jietuopo",
                "westup"    : __DIR__"guiyunge",
        ]));
        set("outdoors", "emei");
        set("no_clean_up", 0);
        set("coor/x", -410);
        set("coor/y", -230);
        set("coor/z", 40);
        setup();
        replace_program(ROOM);
}