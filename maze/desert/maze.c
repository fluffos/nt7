#include <ansi.h>

inherit VRM_SERVER;

#define ENTER_ROOM_X  10000
#define ENTER_ROOM_Y  10000
#define ENTER_ROOM_Z  10000

void create()
{
        //迷宫房间所继承的物件的档案名称。
        set_inherit_room( ROOM );

        //唯一房间
        set_unique_room( ({
                "/maze/desert/unique_room/guai_boss_room",
                "/maze/desert/unique_room/guai_boss_room",
                "/maze/desert/unique_room/guai_boss_room",
                "/maze/desert/unique_room/guai_boss_room",
        }) );
        set_center_room("/maze/desert/unique_room/king_boss_room");

        //迷宫房间里的怪物。
        set_maze_npcs( ([
                "/maze/desert/npc/guai": 1 + random(3),
        ]) );

        set_npcs_rate(80);

        set_lonely_create(1);

        set_maze_boxs(5);


        //迷宫的单边长
        set_maze_long(8);

        //入口方向(出口在对面)
        set_entry_dir("north");

        //入口与区域的连接方向
        set_link_entry_dir("north");

        //入口与区域的连接档案名
        set_link_entry_room("/d/changan/ca10");

        //出口与区域的连接方向
        set_link_exit_dir("south");

        //出口与区域的连接档案名
        set_link_exit_room(__DIR__"out");  


        //普通房间描述
        set_maze_room_short(RED "无尽大漠" NOR);

        set_maze_room_desc(@LONG
一望无际的大漠，烈日、风沙、苦寒、酷热，无时不在折磨着每
一个人，在这里，如果你没有饮水，很有可能就会被晒死，沙子滚烫，
足以把脚烫烂，一到晚上，却又冰冷得透骨。
LONG);

        //入口房间短描述
        set_entry_short(HIR "无尽大漠入口" NOR);

        //入口房间描述
        set_entry_desc(@LONG
一望无际的大漠，烈日、风沙、苦寒、酷热，无时不在折磨着每
一个人，在这里，如果你没有饮水，很有可能就会被晒死，沙子滚烫，
足以把脚烫烂，一到晚上，却又冰冷得透骨。
LONG);

        //出口房间短描述
        set_exit_short(WHT "无尽大漠出口" NOR);

        //出口房间描述
        set_exit_desc(@LONG
一望无际的大漠，烈日、风沙、苦寒、酷热，无时不在折磨着每
一个人，在这里，如果你没有饮水，很有可能就会被晒死，沙子滚烫，
足以把脚烫烂，一到晚上，却又冰冷得透骨。
LONG);
        set_outdoors(1);
}
