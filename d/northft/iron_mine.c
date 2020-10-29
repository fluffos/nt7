// iron_mine.c
// 铁矿场

#include <mine_def.h>

inherit MINE_FIELD;

void create()
{
	set_maze_long(10);				// 矿区单边长
	set_mine_room(__DIR__"mine_room");		// 有矿房间
	set_no_mine_room(__DIR__"no_mine_room");	// 无矿房间
	set_contain_quantity(10000000);			// 单位(两),100万斤
	set_contain_persent(15);			// 蕴藏比例
	set_reset_time_sect(20);			// 再生期（Game年）
	set_mine_class(IRON_MINE);			// 铁矿
	set_entry_dir("west");				// 入口方向
	set_link_entry_dir("west");			// 入口和区域的连接方向
	set_link_entry_room(__DIR__"ftn13");		// 入口所连接区域档案的文件名
        set_outdoors(1); 
}
