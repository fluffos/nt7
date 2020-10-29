
#include <ansi.h>
inherit VRM_SERVER;

void create()
{
        // 迷宫房间所继承的物件的档案名称。
        set_inherit_room( ROOM );

        // 迷宫进入要求最低等级。
        //set_enter_min_level(10);

        // 迷宫进入要求最高等级。
        //set_enter_max_level(20);

        set_lonely_create(1);

        // 迷宫房间时间ID和刷新时间。
        set_remove_time(1800);

        //迷宫房间里的怪物。
        set_maze_npcs(__DIR__"npc/beast");

        // 迷宫中的怪物出现可能性
        set_npcs_rate(50);

        //迷宫房间里的BOSS。
        set_exit_npcs(__DIR__"npc/dragon");

        //迷宫的单边长
        set_maze_long(10);

        //入口方向(出口在对面)
        set_entry_dir("south");

        //入口与区域的连接方向
        set_link_entry_dir("south");

        //入口与区域的连接档案名
        set_link_entry_room("/d/dragon/spiritgate");

        //出口与区域的连接方向
        set_link_exit_dir("north");

        //出口与区域的连接档案名
        set_link_exit_room("/d/dragon/spiritgate");

        //入口房间短描述
        set_entry_short("忘忧园");

        //入口房间描述
        set_entry_desc(@LONG
这儿就是关外的忘忧园。周围阴森森的，只有四个黑乎乎的洞口，
也不知通向何处。
LONG
);

        //BOSS房间短描述
        set_exit_short("沙之底");

        //BOSS房间描述
        set_exit_desc(HIY"

这里就是沙漠尽头。。。。。。
"NOR);

        //迷宫房间的短描述
        set_maze_room_short("忘忧园");

        //迷宫房间的描述，如果有多条描述，制造每个房
        //间的时候会从中随机选择一个。
        set_maze_room_desc(@LONG
这儿就是关外的忘忧园。周围阴森森的，只有四个黑乎乎的洞口，
也不知通向何处。
LONG
);

        // 迷宫房间是否为户外房间？
        //set_outdoors(1);
}

