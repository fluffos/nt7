// This program is a part of NITAN MudLIB

#include <ansi.h>
inherit VRM_SERVER;

void create() 
{ 
        // 迷宫房间所继承的物件的档案名称。 
        set_inherit_room( ROOM );  
                        
        // 唯一房间
        set_unique_room("/d/reborn/unique_room/xinmo_room"); 

        // 迷宫房间里的怪物。 
        set_maze_npcs( ([
                "/d/reborn/npc/shadow": random(2),  
        ]) );   
        
        // 迷宫的单边长 
        set_maze_long(10); 
                        
        // 入口方向(出口在对面) 
        set_entry_dir("north"); 
                        
        // 入口与区域的连接方向 
        set_link_entry_dir("north"); 
                        
        // 入口与区域的连接档案名 
        set_link_entry_room("/d/reborn/jitan1"); 
                        
        // 出口与区域的连接方向 
        set_link_exit_dir("south"); 
                        
        // 出口与区域的连接档案名 
        set_link_exit_room("/d/reborn/jitan1");                        
                        
        // 普通房间描述
        set_maze_room_short(RED "幻境" NOR);
                        
        set_maze_room_desc(@LONG
幻境里到处是迷雾弥漫，周边的景物似有似无，虚无缥缈。
LONG); 
                        
        // 入口房间短描述 
        set_entry_short(HIR "幻境入口" NOR); 
                        
        // 入口房间描述 
        set_entry_desc(@LONG
幻境里到处是迷雾弥漫，周边的景物似有似无，虚无缥缈。
LONG); 
                        
        // 出口房间短描述 
        set_exit_short(HIW "幻境出口" NOR); 
                        
        // 出口房间描述 
        set_exit_desc(@LONG
幻境里到处是迷雾弥漫，周边的景物似有似无，虚无缥缈。
LONG); 

        // 迷宫房间是否为户外房间？ 
        set_outdoors(1); 
        
        set_remove_time(420);
} 

string query_my_map(){  return read_file(__DIR__"maze.map");}

