#include <ansi.h>

inherit VRM_SERVER;

#define ENTER_ROOM_X    0
#define ENTER_ROOM_Y    0
#define ENTER_ROOM_Z    0

void create()
{
        // 迷宫房间所继承的物件的档案名称。
        set_inherit_room( ROOM );


        // 迷宫房间存在的时间。
        set_remove_time(1800);

        set_lonely_create(1);

        //迷宫房间里的怪物。
        set_maze_npcs(__DIR__"npc/beast");

        // 迷宫中的怪物出现可能性
        set_npcs_rate(50);

        //迷宫房间里的BOSS。
        set_exit_npcs(__DIR__"npc/dragon");

        //迷宫的单边长
        set_maze_long(10);

        //入口方向(出口在对面)
        set_entry_dir("east");

        //入口与区域的连接方向
        set_link_entry_dir("east");

        //入口与区域的连接档案名
        set_link_entry_room("/d/xueshan/shenghu");

        //出口与区域的连接方向
        set_link_exit_dir("west");

        //出口与区域的连接档案名
        set_link_exit_room("/d/xueshan/shenghu");

        //入口房间短描述
        set_entry_short("天之尽头");

        //入口房间描述
        set_entry_desc(@LONG
这里风光秀丽，当真是好去处！高崖上视野开阔，远望四周，
把天下景色看的清清楚楚。远处大海如明镜般平整。山崖上长有
无数异草，飘着淡淡香气。天空中的太阳向天边渐渐落下，水中
的阳光朝岸边缓缓游去。
LONG
);

        //BOSS房间短描述
        set_exit_short("天之涯");

        //BOSS房间描述
        set_exit_desc(HIC"

这里就是天之尽头。。。。。。
"NOR);

        //迷宫房间的短描述
        set_maze_room_short("天之尽头");

        //迷宫房间的描述，如果有多条描述，制造每个房
        //间的时候会从中随机选择一个。
        set_maze_room_desc(@LONG
这里风光秀丽，当真是好去处！高崖上视野开阔，远望四周，
把天下景色看的清清楚楚。远处大海如明镜般平整。山崖上长有
无数异草，飘着淡淡香气。天空中的太阳向天边渐渐落下，水中
的阳光朝岸边缓缓游去。
LONG
);

        //以下是入口坐标
        set_link_entry_room_x(ENTER_ROOM_X);
        set_link_entry_room_y(ENTER_ROOM_Y);
        set_link_entry_room_z(ENTER_ROOM_Z);
        
        // 迷宫房间是否为户外房间？
        set_outdoors(1);
}


