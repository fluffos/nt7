// This program is a part of NITAN MudLIB

#include <ansi.h>

inherit VRM_SERVER;

#define ENTER_ROOM_X  10000
#define ENTER_ROOM_Y  10000
#define ENTER_ROOM_Z  10000

void create() 
{ 
        // 迷宫房间所继承的物件的档案名称。 
        set_inherit_room( ROOM );  
                        
        //唯一房间
        set_unique_room( ({
                "/maze/necropolis/unique_room/skeleton_room",
                "/maze/necropolis/unique_room/ghost_room",
                "/maze/necropolis/unique_room/zombie_room",
                "/maze/necropolis/unique_room/rest_room",
                "/maze/necropolis/unique_room/quest_room",
        }) ); 

        //迷宫房间里的怪物。 
        set_maze_npcs( ([
                "/maze/necropolis/npc/skeleton": !random(3),  
                "/maze/necropolis/npc/skeleton_fighter": !random(5),
                "/maze/necropolis/npc/skeleton_mage": !random(5),
                "/maze/necropolis/npc/zombie": !random(3),  
                "/maze/necropolis/npc/zombie_blood": !random(5),
                "/maze/necropolis/npc/zombie_power": !random(5),
                "/maze/necropolis/npc/ghost": !random(3),  
                "/maze/necropolis/npc/ghost_fire": !random(5),
                "/maze/necropolis/npc/ghost_eye": !random(5),
        ]) );        
        //不算死亡                
        //set_maze_nodeath(1);

        set_lonely_create(1);
        
        set_maze_boxs(5);
        //迷宫的单边长 
        set_maze_long(10); 
                        
        //入口方向(出口在对面) 
        set_entry_dir("north"); 
                        
        //入口与区域的连接方向 
        set_link_entry_dir("north"); 
                        
        //入口与区域的连接档案名 
        set_link_entry_room(__DIR__"enter"); 
                        
        //出口与区域的连接方向 
        set_link_exit_dir("south"); 
                        
        //出口与区域的连接档案名 
        set_link_exit_room(__DIR__"leave"); 
                        
        //以下是入口坐标
        set_link_entry_room_x(ENTER_ROOM_X);
        set_link_entry_room_y(ENTER_ROOM_Y);
        set_link_entry_room_z(ENTER_ROOM_Z);
                        
        //普通房间描述
        set_maze_room_short(RED "诡异墓园" NOR);
                        
        set_maze_room_desc(@LONG
墓园里没有一点生气，地上到处是枯枝败叶，偶尔看到一些
干枯的动物尸骸，让人不寒而栗，到处散发着一股尸首腐烂的
味道，看不到一丝活物存在。
LONG); 
                        
        //入口房间短描述 
        set_entry_short(HIR "诡异墓园入口" NOR); 
                        
        //入口房间描述 
        set_entry_desc(@LONG
墓园里没有一点生气，地上到处是枯枝败叶，偶尔看到一些
干枯的动物尸骸，让人不寒而栗，到处散发着一股尸首腐烂的
味道，看不到一丝活物存在。
LONG); 
                        
        //出口房间短描述 
        set_exit_short(HIW "诡异墓园出口" NOR); 
                        
        //出口房间描述 
        set_exit_desc(@LONG
墓园里没有一点生气，地上到处是枯枝败叶，偶尔看到一些
干枯的动物尸骸，让人不寒而栗，到处散发着一股尸首腐烂的
味道，看不到一丝活物存在。
LONG); 

        // 迷宫房间是否为户外房间？ 
        set_outdoors(1); 
        
        set_maze_refresh(600); 
        set_remove_time(1800); 
                                                
} 

