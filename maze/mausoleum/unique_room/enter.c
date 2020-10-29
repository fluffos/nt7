#include <command.h>
inherit ROOM;

void create()
{
        set("short", "内宫通道");
        set("long", @LONG
通道两侧，自东向西依次排列着狮、獬、骆驼、象、麒麟和马六
种石雕巨兽，各有两对四座，共十二对二十四座，造型生动，栩栩如
生，使你像来到了传说的仙界。在淡淡的月照下，众石兽或蹲或立，
不畏风霜雨雪。
LONG );
        set("maze", 1);
        set("no_magic", 1);
        set("virtual_room", 1);
        set("no_clean_up", 1);       
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

void init()
{
        object me;
        string file;
        
        if( !interactive(me = this_player()) || 
            query("init_exits") ) return; 
        
        file = FUBEN_D->query_maze_dir(me); 

        set("exits/northdown", file+"northgate");
        set("exits/southdown", file+"southgate");
        set("exits/westdown",  file+"westgate");
        set("exits/eastdown",  file+"eastgate");
        set("init_exits", 1);
        tell_room(this_object(), "突然四周一阵旋转，等一切安静下来，你发现地板下出现几个洞口。\n");
        LOOK_CMD->look_room(me,this_object(),query("env/brief", me));
        return;
}
