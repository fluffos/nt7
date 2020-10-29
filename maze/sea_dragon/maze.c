#include <ansi.h>

inherit VRM_SERVER;

#define ENTER_ROOM_X    0
#define ENTER_ROOM_Y    0
#define ENTER_ROOM_Z    0

void create()
{
        // 迷宫房间所继承的物件的档案名称。
        set_inherit_room( ROOM );

        set_lonely_create(1);
        // 迷宫进入要求最低等级。

        // 迷宫进入要求最高等级。

        // 迷宫房间存在的时间。
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
        set_entry_dir("north");

        //入口与区域的连接方向
        set_link_entry_dir("north");

        //入口与区域的连接档案名
        set_link_entry_room("/d/xiakedao/haibin");

        //出口与区域的连接方向
        set_link_exit_dir("south");

        //出口与区域的连接档案名
        set_link_exit_room("/d/xiakedao/haibin");

        //入口房间短描述
        set_entry_short("海底迷宫");

        //入口房间描述
        set_entry_desc(@LONG
这里水色变的浑浊起来，周围已看不大清楚了。偶有暗流袭来，卷
起阵阵的泥流。四处长着些高高的海草，密密麻麻把头上遮的一丝
光芒也没有了。
LONG
);

        //BOSS房间短描述
        set_exit_short("海之角");

        //BOSS房间描述
        set_exit_desc(HIB"

这里就是海的尽头了。。。。。。
"NOR);

        //迷宫房间的短描述
        set_maze_room_short("海底迷宫");

        //迷宫房间的描述，如果有多条描述，制造每个房
        //间的时候会从中随机选择一个。
        set_maze_room_desc(@LONG
这里水色变的浑浊起来，周围已看不大清楚了。偶有暗流袭来，卷
起阵阵的泥流。四处长着些高高的海草，密密麻麻把头上遮的一丝
光芒也没有了。
LONG
);

        //以下是入口坐标
        set_link_entry_room_x(ENTER_ROOM_X);
        set_link_entry_room_y(ENTER_ROOM_Y);
        set_link_entry_room_z(ENTER_ROOM_Z);
        
        // 迷宫房间是否为户外房间？
        //set_outdoors(1);
}


