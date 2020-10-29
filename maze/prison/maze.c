#include <ansi.h>

inherit VRM_SERVER;

#define ENTER_ROOM_X  10000
#define ENTER_ROOM_Y  10000
#define ENTER_ROOM_Z  10000

void create() 
{ 
        // 迷宫房间所继承的物件的档案名称。 
        set_inherit_room( ROOM );  
                        
        //迷宫房间里的怪物。 
        set_maze_npcs( ([
                "/maze/prison/npc/qiutu1": 1 + random(2),
                "/maze/prison/npc/qiutu2": 1 + random(2),
                "/maze/prison/npc/qiutu3": 1 + random(2),
                "/maze/prison/npc/jinyiwei": 1 + random(2),
        ]) );                   

        set_exit_npcs( "/maze/prison/npc/laotou" );
        //不算死亡              
        //set_no_death_room(1);
        
        //迷宫的单边长 
        set_maze_long(8); 

        set_maze_boxs(5);
                        
        //入口方向(出口在对面) 
        set_entry_dir("north"); 
                        
        //入口与区域的连接方向 
        set_link_entry_dir("north"); 
                        
        //入口与区域的连接档案名 
        set_link_entry_room(__DIR__"enter"); 
                        
        //出口与区域的连接方向 
        set_link_exit_dir("south"); 
                        
        //出口与区域的连接档案名 
        set_link_exit_room(__DIR__"out"); 
                        
        //以下是入口坐标
        //set_link_entry_room_x(ENTER_ROOM_X);
        //set_link_entry_room_y(ENTER_ROOM_Y);
        //set_link_entry_room_z(ENTER_ROOM_Z);
                        
        //普通房间描述
        set_maze_room_short(RED "天牢" NOR);
                        
        set_maze_room_desc(@LONG
这里黑沉沉的，即无一丝光亮，也无半分声息。黑暗中依稀可以
看到身边似乎有几个人影，看到你转过头去，他们立刻屏住呼吸，紧
张地瞪着你。四壁摸上去冰凉，且极硬，似乎都是钢铁铸成。脚边有
一堆东西踢上去克剌剌地散了开来，细看却是一具白得发亮的枯骨。
LONG); 
                        
        //入口房间短描述 
        set_entry_short(HIR "天牢入口" NOR); 
                        
        //入口房间描述 
        set_entry_desc(@LONG
这里黑沉沉的，即无一丝光亮，也无半分声息。黑暗中依稀可以
看到身边似乎有几个人影，看到你转过头去，他们立刻屏住呼吸，紧
张地瞪着你。四壁摸上去冰凉，且极硬，似乎都是钢铁铸成。脚边有
一堆东西踢上去克剌剌地散了开来，细看却是一具白得发亮的枯骨。
LONG); 
                        
        //出口房间短描述 
        set_exit_short(HIW "天牢出口" NOR); 
                        
        //出口房间描述 
        set_exit_desc(@LONG
这里黑沉沉的，即无一丝光亮，也无半分声息。黑暗中依稀可以
看到身边似乎有几个人影，看到你转过头去，他们立刻屏住呼吸，紧
张地瞪着你。四壁摸上去冰凉，且极硬，似乎都是钢铁铸成。脚边有
一堆东西踢上去克剌剌地散了开来，细看却是一具白得发亮的枯骨。
LONG); 

        // 迷宫房间是否为户外房间？ 
        // set_outdoors(1); 
        
} 


