// This program is a part of NITAN MudLIB

#include <ansi.h>

inherit VRM_SERVER;

void create() 
{ 
        //迷宫房间所继承的物件的档案名称。 
        set_inherit_room( ROOM );  
                        
        //唯一房间
        set_unique_room( ({
                "/maze/temple/unique_room/zombie_room",
        }) ); 

        //迷宫房间里的怪物。 
        set_maze_npcs( ([
                "/maze/temple/npc/zombie": 3,  
                "/maze/temple/npc/zombie_lord": !random(5),
        ]) );
        
        set_lonely_create(1);
        
        set_maze_boxs(5); 
        
        //set_maze_traps(6); 

        //迷宫的单边长 
        set_maze_long(10); 
                        
        //入口方向(出口在对面) 
        set_entry_dir("north"); 
                        
        //入口与区域的连接方向 
        set_link_entry_dir("north"); 
                        
        //入口与区域的连接档案名 
        set_link_entry_room("/d/city/wumiao"); 
                        
        //出口与区域的连接方向 
        set_link_exit_dir("south"); 
                        
        //出口与区域的连接档案名 
        set_link_exit_room("/d/city/wumiao"); 
                        
                        
        //普通房间描述
        set_maze_room_short(RED "失落神庙" NOR);
                        
        set_maze_room_desc(@LONG
神庙很大，柱子上雕刻着千奇百怪的动物，有的人身上却
长着一颗狼头，人身上生出一双翅膀，怪异的怪首的雕刻让人
叹为观止，庙顶成八角，屋脊曲线柔美,泥塑,剪黏,木雕,彩绘
皆为上品。
LONG); 
                        
        //入口房间短描述 
        set_entry_short(HIR "失落神庙入口" NOR); 
                        
        //入口房间描述 
        set_entry_desc(@LONG
神庙很大，柱子上雕刻着千奇百怪的动物，有的人身上却
长着一颗狼头，人身上生出一双翅膀，怪异的怪首的雕刻让人
叹为观止，庙顶成八角，屋脊曲线柔美,泥塑,剪黏,木雕,彩绘
皆为上品。
LONG); 
                        
        //出口房间短描述 
        set_exit_short(HIW "失落神庙出口" NOR); 
                        
        //出口房间描述 
        set_exit_desc(@LONG
神庙很大，柱子上雕刻着千奇百怪的动物，有的人身上却
长着一颗狼头，人身上生出一双翅膀，怪异的怪首的雕刻让人
叹为观止，庙顶成八角，屋脊曲线柔美,泥塑,剪黏,木雕,彩绘
皆为上品。
LONG); 
                                              
} 

