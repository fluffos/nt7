#include <ansi.h>
inherit ROOM;

string look_door();
void create()
{
        set("short", HIR "秦陵内宫东门" NOR);
        set("long", @LONG
通道两侧，自东向西依次排列着狮、獬、骆驼、象、麒麟和马六
种石雕巨兽，各有两对四座，共十二对二十四座，造型生动，栩栩如
生，使你像来到了传说的仙界。在淡淡的月照下，众石兽或蹲或立，
不畏风霜雨雪，前面通向秦陵内宫，但是被一个巨大的石门（door）
封住了，，石门上却插着四把形状奇特火炬（huoju）。 细看石门周
围，只见有四个像是人工开凿小山洞。
LONG );
        set("maze", 1);
        set("no_magic", 1);
        set("virtual_room", 1);
        set("no_clean_up", 1);
        set("item_desc", ([
               "door"   : (: look_door :),
               "huoju"  : HIR "这些火炬看来很奇怪，似乎连接着什么机关！\n" NOR,
        ]));

        set("exits", ([
                //"west" : __DIR__"maze1/entry",
                "westup" : __DIR__"maze/5/5",
        ]));

        /*
        set("objects", ([
                "/maze/mausoleum/npc/jiangling": 1,
                "/maze/mausoleum/npc/qianrenzhang": 1,
                "/maze/mausoleum/npc/bairenzhang": 2,
                "/maze/mausoleum/npc/bingshi": 3,
                "/maze/mausoleum/npc/baozi": 2,
                "/maze/mausoleum/npc/tiger": 2,
                "/maze/mausoleum/npc/lions": 1,
                "/maze/mausoleum/npc/ni": 1,
                "/maze/mausoleum/npc/mammoth": 1,
        ]));
        */
        setup();
}

string look_door()
{
        object ob, me;
        int n;
        string opened, msg, temp;

        mapping change_num = ([
               "1" : "一",
               "2" : "二",
               "3" : "三",
               "4" : "四",
        ]);

        me = this_player();
        ob = FUBEN_D->query_maze_mainobj(me);

        if (! objectp(ob))
               return "TSR 物件出错，请与巫师联系！\n";

        opened=query("lock/opened", ob);

        if (opened == "" || ! stringp(opened))
               return "只见石门紧闭，上面插着四把火炬（huoju），但都熄灭了！\n";

        if( TIME_D->realtime_digital_clock()[0..3] != "凌晨" )
               return "只见石门紧闭，上面插着四把火炬（huoju），但都熄灭了！\n";

        if( query("lock/unlocked", ob) && sizeof(opened) == 4 )
               return NOR + WHT "\n只见石门陷入地下，四把火炬烧得正旺！一个入口露了出来。\n" NOR;

        msg = HIC "只见石门紧闭，第";
        for (n = 0; n < sizeof(opened); n ++)
        {
              temp = opened[n..n];
              msg += change_num[temp];
              if (n < sizeof(opened) - 1)msg += "、" ;
        }
        msg += "把火炬燃烧着！\n" NOR;

        return msg;

}
