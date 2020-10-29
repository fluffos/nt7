#include <ansi.h>
inherit "/adm/daemons/vrm_server.c";

#define ENTER_ROOM_X  0
#define ENTER_ROOM_Y  0
#define ENTER_ROOM_Z  0
 
void create() 
{ 
        set_lonely_create(1);
        
        //迷宫房间所继承的物件的档案名称。 
        set_inherit_room( ROOM ); 
        
        //迷宫的单边长 
        set_maze_long(8); 
        
        set_maze_boxs(3);
        
        //set_maze_traps(3);
                        
        //入口方向(出口在对面) 
        set_entry_dir("east"); 
                        
        //出口与区域的连接方向 
        set_link_exit_dir("west"); 
                        
        //出口与区域的连接档案名 
        set_link_exit_room(__DIR__"leave"); 

        //以下是入口坐标 
        set_link_entry_room_x(ENTER_ROOM_X); 
        set_link_entry_room_y(ENTER_ROOM_Y); 
        set_link_entry_room_z(ENTER_ROOM_Z); 
                        
        //普通房间描述
        set_maze_room_short("迷宫");
                        
        set_maze_room_desc(@LONG
这是一间宽敞的石屋，四周巨石垒就的墙壁泛出幽幽的青色光芒，两盏青铜
灯吐出一尺高的火焰，飘忽闪烁，偶然有灯花爆裂的轻响，更令人感到窒息般的
寂静。地上是丈许见方的青石板铺就，房间中央一块白色石板格外醒目，上面雕
刻着细密的图纹，让人不由自主的想上前查看（mazemap）一番。
LONG); 

        //入口房间短描述 
        set_entry_short("迷宫入口"); 
                        
        //入口房间描述 
        set_entry_desc(@LONG
这是一间宽敞的石屋，四周巨石垒就的墙壁泛出幽幽的青色光芒，两盏青铜
灯吐出一尺高的火焰，飘忽闪烁，偶然有灯花爆裂的轻响，更令人感到窒息般的
寂静。地上是丈许见方的青石板铺就，房间中央一块白色石板格外醒目，上面雕
刻着细密的图纹，让人不由自主的想上前查看（mazemap）一番。
LONG);
                        
        //出口房间短描述 
        set_exit_short("迷宫出口"); 
                        
        //出口房间描述 
        set_exit_desc(@LONG
这是一间宽敞的石屋，四周巨石垒就的墙壁泛出幽幽的青色光芒，两盏青铜
灯吐出一尺高的火焰，飘忽闪烁，偶然有灯花爆裂的轻响，更令人感到窒息般的
寂静。地上是丈许见方的青石板铺就，房间中央一块白色石板格外醒目，上面雕
刻着细密的图纹，让人不由自主的想上前查看（mazemap）一番。
LONG);
 
        // 迷宫限制最高进入等级
        set_remove_time(1800); 
} 


