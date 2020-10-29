// This program is a part of NITAN MudLIB

/******************************************************
 * vrm_server.c                                       *
 * 虚拟的随机迷宫创造器 (Virtual Random Maze)         *
 *                                                    *
 * Written by Find.                                   *
 * Rewritten by Lonely@nitan.org                      *
 ******************************************************/

/******************************************************
 * 随机迷宫的产生算法尽量简单，迷宫的储存尽量节省记忆 *
 * 体，迷宫房间采用虚拟物件，处理灵活，迷宫房间只有在 *
 * 玩家走到时才会装进内存，而且迷宫房间也象普通的ROOM *
 * 一样当一段时间没有被参考到可以销毁节省记忆体，当整 *
 * 个迷宫一段时间没有被参考到可以被完全摧毁，下次再需 *
 * 要的时候会重新建立，又会产生一个新的迷宫。区域巫师 *
 * 写作随机迷宫只需规定一些预设的参数如迷宫的单边长、 *
 * 房间描述、出入口描述，几十个乃至几千个房间、路线时 *
 * 时不同的随机迷宫就建立好了，大大提高了区域写作效率 *
 * 和游戏的可玩性。                                   *
 * 此物件目前适合于随机的迷宫，即：迷宫内房间的描述基 *
 * 本相同，比如一片树林、一片坟地等，如要此物件创作完 *
 * 整的随机区域即有一定的情节、一定格局的区域，则需要 *
 * 根据自己的情况规定出迷宫内房间描述的一些规则，使相 *
 * 邻房间的描述变化合理，房间内物件与描述协调。       *
 * 由于采用virtual object，牵涉到一点安全问题，需要根 *
 * 据自己的系统考量调整。                             *
 * 增加了迷宫生成新的算法，主要用于详细显示迷宫的路径 *
 * 和宝箱以及陷阱等其他功能(by Lonely)。              *
 ******************************************************/

// #pragma optimize

#define CENTER          4096    // 正中心的房间
#define TRAP            2048    // 有陷阱的房间
#define BOX             1024    // 有宝箱的房间
#define MAP             512     // 有地图的房间
#define SPECIAL         256     // 特殊的房间
#define T               128     // 正在处理的房间
#define B               64      // 呆死的房间
#define R               32      // 路线上的房间
#define D               16      // 初始化后的房间
#define N               8       // 向北出口
#define S               4       // 向南出口
#define W               2       // 向西出口
#define E               1       // 向东出口
#define ALL             15      // 所有出口
#define MAX_LONG        100     // 最大边长

#define RESET           CENTER | TRAP | BOX | MAP | SPECIAL
#define BOX_OB          "/clone/misc/baoxiang"
#define TRAP_ROOM       "/inherit/room/trap"

#define TWO_VALID_LEAVES  // 规定房间最多只能有两个出口
#define MAP_COMM    1     // 迷宫地图是普通模式
#define MAP_DEEP    2     // 迷宫地图是详细模式
#define MAP_NONE    3     // 迷宫地图是关闭模式
#define BUSY        1     // 让玩家BUSY
#define TRIP        2     // 让玩家摔到别的房间
#define LOSTMAP     3     // 让迷宫地图失效
#define CHANGEMAP   4     // 让迷宫地图刷新
#define WOUND       5     // 让玩家受伤
#define SPECIAL_MAP 1     // 迷宫地图变为详细模式
#define SPECIAL_DAN 2     // 仙丹等物品
#define JINKUAI     3     // 金块等物品
#define GOLD        4     // 黄金
#define OBJ         5     // 任务物品
#define SPECIAL_OBJ 6     // 英雄商店出售的物品
#define NPC_SKILL   7     // 降低NPC的武功

#include <ansi.h>
inherit F_CLEAN_UP;
inherit F_DBASE;

class coordinate{ int x; int y; }
class coordinate *newpath = ({}), *badpath = ({}), *roadpath = ({}),
        enter,/* 入口坐标 */
        leave;/* 出口坐标 */

nosave string *valid_dirs = ({ "south","north","west","east" });
nosave mapping reverse_dir = ([
"north" : "south",
"south" : "north",
"west"  : "east",
"east"  : "west",
]);

// 全迷宫出口阵列.
nosave mixed *all;
// 迷宫地图阵列
nosave mixed line, line2;

/***************** 迷宫的一些预设特性：*****************/
nosave int l;                           // 迷宫的单边长
nosave string *inherit_rooms = ({});    // 迷宫允许继承的档案名称
nosave string *valid_rooms = ({});      // 迷宫可使用的房间文件名 (****)
nosave string entry_dir;                // 迷宫入口方向
nosave string link_entry_dir;           // 迷宫入口与区域的连接方向
nosave string link_entry_room;          // 迷宫入口所连接区域档案的文件名
private int link_entry_room_x;          // 迷宫入口的x坐标
private int link_entry_room_y;          // 迷宫入口的y坐标
private int link_entry_room_z;          // 迷宫入口的z坐标
nosave string link_exit_dir;            // 迷宫出口与区域的连接方向
nosave string link_exit_room;           // 迷宫出口所连接区域档案的文件名
nosave string entry_short;              // 迷宫入口的短描述
nosave string entry_desc;               // 迷宫入口的长描述
nosave string exit_short;               // 迷宫出口的短描述
nosave string exit_desc;                // 迷宫出口的长描述
nosave string center_room;              // 迷宫中心位置房间
nosave string *maze_room_desc = ({});   // 迷宫房间的长描述
nosave string maze_room_short;          // 迷宫房间的短描述
nosave int is_outdoors = 0;             // 迷宫房间是否为户外
nosave mixed maze_npcs;                 // 迷宫中的怪物
nosave mixed entry_npcs;                // 迷宫入口的怪物
nosave mixed exit_npcs;                 // 迷宫出口的怪物
nosave string *unique_rooms = ({});     // 迷宫唯一的房间
nosave string *special_rooms = ({});    // 迷宫特殊的房间
private int refresh_delay = 0;          // 迷宫重建时间, default is 0 means no recreation
nosave int is_nodeath = 0;              // 迷宫不死房间
nosave int random_rate = 0;             // 迷宫怪物出现几率
nosave int remove_time = 0;             // 迷宫销毁时间
nosave int box_num = 0;                 // 迷宫宝箱的数量
nosave int trap_num = 0;                // 迷宫陷阱的数量
nosave int normal_room = 0;
nosave int lonely_create = 0;           // 迷宫创建新模式(Lonely)
/******************* ---- END ---- *********************/

nosave int handle_id;                   // 排程
nosave int return_dir = 0;              // 迷宫入口方向
nosave int map_status = MAP_COMM;       // 迷宫的地图状态
nosave int display_coordinate = 1;      // 是否显示玩家所在的位置
nosave object maze_boss;                // 迷宫里的BOSS

// 建立标记.
nosave int maze_built = 0;

// 迷宫房间来源转换开关
nosave int switch_flag = 0;

// 重置全域变量.
protected void refresh_vars();

// 建立迷宫
void create_maze();
void init_line();
varargs void init_maze(object room);
void init_road();
void init_room();
void init_special();

// 选择随机出口.
protected varargs int random_out(int x,int y,int n);

// 处理连接.
protected void link_to_north(int x,int y);
protected void link_to_south(int x,int y);
protected void link_to_west(int x,int y);
protected void link_to_east(int x,int y);
protected void init_to_north(int x,int y);
protected void init_to_south(int x,int y);
protected void init_to_west(int x,int y);
protected void init_to_east(int x,int y);
protected mixed init_to_link(int x,int y);

nomask object query_maze_room(string str);
int query_maze_length(){ return l; }
protected string mroom_fname(int x,int y)
{ return sprintf("%s/%d/%d",base_name(this_object()),x,y);}

public mixed query_roadpath() { return roadpath; }
public mixed query_badpath() { return badpath; }
public mixed query_maze_boss() { return objectp(maze_boss) ? maze_boss : 0; }
public int query_map_status() { return map_status; }
public int query_remove_time() { return remove_time; }
public int is_maze() { return 1; }
int is_player_in(object room);
protected void refresh_vars() // 重置全域变量.
{
        newpath = ({});
        badpath = ({});
        roadpath = ({});
        all = 0;
        line = 0;
        line2 = 0;
}

// 对一些必设参数的合法性检查
protected int check_vars()
{
        int i,n;

        if( (l < 5) || l > MAX_LONG )
                return 0;

        if( !switch_flag ) {
                if( !stringp(entry_dir) || (member_array(entry_dir,valid_dirs) == -1) )
                        return 0;

                maze_room_desc -=({0});
                if( !n = sizeof(maze_room_desc) )
                        return 0;

                for( i=0;i<n;i++ )
                        if( !stringp(maze_room_desc[i]) || (maze_room_desc[i] == "") )
                                return 0;

                if( !stringp(maze_room_short) || (maze_room_short == "") )
                        return 0;
        } else {
                valid_rooms -=({0});
                if( !n = sizeof(valid_rooms) )
                        return 0;
                for( i=0;i<n;i++ )
                        if( !stringp(valid_rooms[i]) || (valid_rooms[i] == "") )
                                return 0;
        }
        /*
        if(!stringp(link_entry_dir) || (member_array(link_entry_dir,valid_dirs) == -1) )
                return 0;

        if(!stringp(link_exit_dir) || (member_array(link_exit_dir,valid_dirs) == -1) )
                return 0;
        */

        inherit_rooms -=({0});
        if( !n = sizeof(inherit_rooms) )
                return 0;

        for( i=0;i<n;i++ )
                if( !stringp(inherit_rooms[i]) || (inherit_rooms[i] == "") )
                        return 0;
        /*
        if( !stringp(link_entry_room) || (link_entry_room == "") )
                return 0;

        if( !stringp(link_exit_room) || (link_exit_room == "") )
                return 0;
        */
        if( !stringp(entry_short) || (entry_short == "") )
                return 0;

        if( !stringp(exit_short) || (exit_short == "") )
                return 0;

        if( !stringp(entry_desc) || (entry_desc == "") )
                return 0;

        if( !stringp(exit_desc) || (exit_desc == "") )
                return 0;

        return 1;
}

protected varargs int random_out(int x,int y,int n,int t) // 选择随机出口函数.
{
        int *outs = ({}), retn = 0;

        // The west room is (x-1,y)
        if( n&W
        && ((x-1) >= 0)
        && !(all[x-1][y]&D) )
        {
                if( !t ) {
                        if( lonely_create > 0 ) {
                                // 迷宫的路径延伸方向不能有返回入口的方向
                                if( !(return_dir&W)
                                && (y != leave->y || x > leave->x) )
                                        outs += ({ W });
                        } else
                                outs += ({ W });
                } else {
                        // 一半的几率岔路这个方向不通
                        if( random(2) == 1 )
                                outs += ({ W });
                }
        }

        // The east room is (x+1,y)
        if( n&E
        && ((x+1) < l)
        && !(all[x+1][y]&D) )
        {
                if( !t ) {
                        if( lonely_create > 0 ) {
                                if( !(return_dir&E)
                                && (y != leave->y || x < leave->x) )
                                        outs += ({ E });
                        } else
                                outs += ({ E });
                } else {
                        if( random(2) == 1 )
                                outs += ({ E });
                }
        }

        // The south room is (x,y-1)
        if( n&S
        && ((y-1) >= 0)
        && !(all[x][y-1]&D) )
        {
                if( !t ) {
                        if( lonely_create > 0 ) {
                                if( !(return_dir&S)
                                && (x != leave->x || y > leave->y) )
                                        outs += ({ S });
                        } else
                                outs += ({ S });
                } else {
                        if( random(2) == 1 )
                                outs += ({ S });
                }
        }

        // The north room is (x,y+1)
        if( n&N
        && ((y+1) < l)
        && !(all[x][y+1]&D) )
        {
                if( !t ) {
                        if( lonely_create > 0 ) {
                                if( !(return_dir&N)
                                && (x != leave->x || y < leave->y) )
                                        outs += ({ N });
                        } else
                                outs += ({ N });
                } else {
                        if( random(2) == 1 )
                                outs += ({ N });
                }
        }

#ifdef TWO_VALID_LEAVES
        // 如果有三个出口,随机关闭一个.
        if( sizeof(outs) >= 3 )
                outs -= ({ outs[random(sizeof(outs))] });
#endif

        if( !t ) {
                // 这里区分创建的迷宫的类型
                if( lonely_create > 0 ) {
                        while( sizeof(outs) > 1 )
                                outs -= ({ outs[random(sizeof(outs))] });
                }
        }

        for( int i=0;i<sizeof(outs);i++ )
                retn |= outs[i];

        return retn;
}

void create_maze()
{
        int i;

        refresh_vars();         // 重置全域变量.
        if( !check_vars() )     // 对一些预设变量进行检查。
                return;

        all = allocate(l);
        for( i=0;i<l;i++ )
                all[i] = allocate(l);   //建立数组.

        enter = new(class coordinate);
        leave = new(class coordinate);

        switch( entry_dir ) {
                case "south":
                        // enter 入口坐标.
                        return_dir |= S;         // 路径往入口的方向
                        enter->x = to_int(l/2); // 取中迷宫比较平衡
                        enter->y = 0;
                        all[enter->x][enter->y] |= S; // | 是 位 操作的或
                        all[enter->x][enter->y] |= D;
                        if( lonely_create > 0 ) {     // 详细地图模式则先要确定出口房间
                                leave->x = random(l);
                                leave->y = l-1;
                        }
                        break;
                case "north":
                        return_dir |= N;
                        enter->x = to_int(l/2);
                        enter->y = l-1;
                        all[enter->x][enter->y] |= N;
                        all[enter->x][enter->y] |= D;
                        if( lonely_create > 0 ) {
                                leave->x = random(l);
                                leave->y = 0;
                        }
                        break;
                case "west":
                        return_dir |= W;
                        enter->y = to_int(l/2);
                        enter->x = 0;
                        all[enter->x][enter->y] |= W;
                        all[enter->x][enter->y] |= D;
                        if( lonely_create > 0 ) {
                                leave->x = l-1;
                                leave->y = random(l);
                        }
                        break;
                case "east":
                        return_dir |= E;
                        enter->y = to_int(l/2);
                        enter->x = l-1;
                        all[enter->x][enter->y] |= E;
                        all[enter->x][enter->y] |= D;
                        if( lonely_create > 0 ) {
                                leave->x = 0;
                                leave->y = random(l);
                        }
                        break;
        }

        // 给迷宫分布宝箱和陷阱
        init_special();

        // 创建迷宫布局
        init_maze();

        // 迷宫定时刷新
        if( refresh_delay > 0 )
                SCHEDULE_D->set_event(refresh_delay, 1, this_object(), "refresh_maze");
}

varargs void init_maze(object room)
{
        int i, x, y, exits;
        class coordinate temp, *valid_leaves = ({});
        string file, fname = base_name(this_object());
        object *temp_rooms = ({}), maze;

        if( objectp(room) ) {
                if( objectp(maze_boss) ) {
                        file = base_name(environment(maze_boss));
                        maze_boss->move(VOID_OB);
                }
                for( x=0;x<l;x++ ) {
                        for( y=0;y<l;y++ ) {
                                all[x][y] &= RESET; // 重新部分数据初始化
                                if( objectp(maze = find_object(sprintf("%s/%d/%d",fname,x,y))) ) {
                                        if( is_player_in(maze) ) {
                                                tell_room(maze, HIR "你听到阵阵沉闷的声音从地下响起...\n"
                                                                HIR "只见四周光影晃动，整个房间似乎在快速移动，等一切安静下来，周遭景象似乎有所改变。\n" NOR);
                                                delete("exits", maze);
                                                temp_rooms += ({ maze });
                                        } else
                                                destruct(maze);
                                }
                        }
                }
                if( maze = find_object(sprintf("%s/entry",fname)) )
                        destruct(maze);
                if( maze = find_object(sprintf("%s/exit",fname)) )
                        destruct(maze);

                special_rooms = copy(unique_rooms);

                switch( entry_dir ) {
                case "south":
                        all[enter->x][enter->y] |= S; // | 是 位 操作的或
                        all[enter->x][enter->y] |= D;
                        break;
                case "north":
                        all[enter->x][enter->y] |= N;
                        all[enter->x][enter->y] |= D;
                        break;
                case "west":
                        all[enter->x][enter->y] |= W;
                        all[enter->x][enter->y] |= D;
                        break;
                case "east":
                        all[enter->x][enter->y] |= E;
                        all[enter->x][enter->y] |= D;
                        break;
                }
        }

        // 初始化地图
        init_line();
        // 初始化路径
        init_road();
        // 制造岔路及打通所有其他房间
        init_room();

        if( !lonely_create ) {
                switch( entry_dir )
                {
                case "west":
                        for( i=0;i<l;i++ )
                                if( all[l-1][i] ) {
                                        temp = new(class coordinate);
                                        temp->x = l-1;
                                        temp->y = i;
                                        valid_leaves += ({temp});
                                }
                        break;
                case "east":
                        for( i=0;i<l;i++ )
                                if( all[0][i] ) {
                                        temp = new(class coordinate);
                                        temp->x = 0;
                                        temp->y = i;
                                        valid_leaves += ({temp});
                                }
                        break;
                case "south":
                        for( i=0;i<l;i++ )
                                if( all[i][l-1] ) {
                                        temp = new(class coordinate);
                                        temp->x = i;
                                        temp->y = l-1;
                                        valid_leaves += ({temp});
                                }
                        break;
                case "north":
                        for( i=0;i<l;i++ )
                                if( all[i][0] ) {
                                        temp = new(class coordinate);
                                        temp->x = i;
                                        temp->y = 0;
                                        valid_leaves += ({temp});
                                }
                        break;
                }

                if( !(i=sizeof(valid_leaves)) ) { // 没有出口 须重新建立
                        //log_file("static/maze",sprintf("%O\n",all));
                        call_other(this_object(),"create_maze");
                        return;
                }

                if( i == 1 )
                        leave = valid_leaves[0];
                else
                        leave = valid_leaves[random(i)]; // 随机选一个.
        }

        switch (entry_dir)
        {
                case "south":
                        all[leave->x][leave->y] |= N;
                        break;
                case "north":
                        all[leave->x][leave->y] |= S;
                        break;
                case "west":
                        all[leave->x][leave->y] |= E;
                        break;
                case "east":
                        all[leave->x][leave->y] |= W;
                        break;
        }

        line[leave->x*2+1][leave->y*2+1] =  HBRED "  " NOR;
        line2[leave->x*2+1][leave->y*2+1] = HBRED "  " NOR;

        // 迷宫创建完毕。
        maze_built = 1;

        if( objectp(room) || sizeof(temp_rooms) > 0 ) {
                if( objectp(maze_boss) )
                        maze_boss->move(load_object(file));

                for( i=0;i<sizeof(temp_rooms);i++ ) {
                        maze = temp_rooms[i];
                        if( sscanf(base_name(maze), fname+"/%d/%d", x, y) != 2 )
                                return;

                        if( !exits = all[x][y] ) return;

                        if( exits&W ) set("exits/west",mroom_fname(x-1,y),maze);
                        else    set("exits/west",mroom_fname(x,y), maze);

                        if( exits&E ) set("exits/east",mroom_fname(x+1,y),maze);
                        else    set("exits/east",mroom_fname(x,y),maze);

                        if( exits&N ) set("exits/north",mroom_fname(x,y+1),maze);
                        else    set("exits/north",mroom_fname(x,y),maze);

                        if( exits&S ) set("exits/south",mroom_fname(x,y-1),maze);
                        else    set("exits/south",mroom_fname(x,y),maze);

                        if( x == enter->x && y == enter->y )
                                set(sprintf("exits/%s",entry_dir),
                                        sprintf("%s/entry",fname), maze);
                        if( x == leave->x && y == leave->y )
                                set(sprintf("exits/%s",reverse_dir[entry_dir]),
                                        sprintf("%s/exit",fname), maze);
                }
        }
}

void init_road()
{

        int x, y, out, numb;
        class coordinate *valid_leaves = ({});

        // 存入待处理队列.
        newpath += ({ enter });
        roadpath += ({ enter });

        // 进入主循环.
        do {
                // 进行一些监测与初始化.
                if( !(numb=sizeof(newpath)) )
                        continue;
                numb = random(numb);
                reset_eval_cost();
                x = newpath[numb]->x;
                y = newpath[numb]->y;

                // 如果有三个可能的出口随机关闭一个出口:
                out = ALL^(all[x][y]); // ^ 是 异或 运算
                out = random_out(x,y,out);

                if( !out ) { // 没有可能的出口了.
                        newpath -= ({ newpath[numb] });
                        continue;
                }

                // 处理连接.
                if( out&W ) link_to_west(x,y);
                if( out&E ) link_to_east(x,y);
                if( out&N ) link_to_north(x,y);
                if( out&S ) link_to_south(x,y);

                // 当前房间处理完毕.
                newpath -= ({ newpath[numb] });
        }
        while( sizeof(newpath) );
}

void init_room()
{
        int i, j, x, y, out, numb, flag;
        class coordinate *valid_leaves = ({});
        //class coordinate tmp1, tmp2;
        mixed deadroom;
        mixed *alldead = ({});

        if( !lonely_create ) return;

        // 给路线上的房间制造岔路
        do {
                // 进行一些监测与初始化.
                if( !(numb=sizeof(roadpath)) )
                        continue;
                numb = random(numb);
                reset_eval_cost();
                x = roadpath[numb]->x;
                y = roadpath[numb]->y;

                out = ALL^(all[x][y]); // ^ 是 异或 运算
                out = random_out(x,y,out,1);

                if( !out ) { // 没有可能的出口了.
                        roadpath -= ({ roadpath[numb] });
                        continue;
                }

                // 处理连接.
                if( out&W ) init_to_west(x,y);
                if( out&E ) init_to_east(x,y);
                if( out&N ) init_to_north(x,y);
                if( out&S ) init_to_south(x,y);

                // 当前房间处理完毕.
                roadpath -= ({ roadpath[numb] });
        }
        while( sizeof(roadpath) );

        // 打通所有没有连接的房间
        for( i=0;i<l;i++ ) {
                for( j=0;j<l;j++ ) {
                        if( !(all[i][j]&D) ) {
                                // 处理的方式有将坏死的房间直接连接到正常房间(降低迷宫复杂度不采用)
                                // 或者是将坏死的房间随机连接,有可能会是死胡同,因此需要二次处理
                                deadroom = init_to_link(i,j);
                                if( sizeof(deadroom) > 0 )
                                        alldead += ({ deadroom });
                        }
                }
        }

        while( sizeof(alldead) ) { // 二次循环处理坏死的房间,直接连接到正常的房间
                for( i=0;i<sizeof(alldead);i++ ) {
                        flag = 0;
                        for( j=0;j<sizeof(alldead[i]);j++ ) {
/*
                                tmp1 = alldead[i][j];
                                x = tmp1->x;
                                y = tmp1->y;
*/
                                x = (alldead[i][j])->x;
                                y = (alldead[i][j])->y;
                                if( ((x-1) >= 0)
                                && !(all[x][y]&W)
                                && !(all[x-1][y]&B) ) {
                                        all[x][y] |= W;
                                        all[x-1][y] |= E;
                                        line[x*2][y*2+1] =  "  ";
                                        line2[x*2][y*2+1] = "  ";
                                        flag = 1;
                                        break;
                                }
                                if( ((x+1) < l)
                                && !(all[x][y]&E)
                                && !(all[x+1][y]&B) )  {
                                        all[x][y] |= E;
                                        all[x+1][y] |= W;
                                        line[x*2+2][y*2+1] =  "  ";
                                        line2[x*2+2][y*2+1] = "  ";
                                        flag = 1;
                                        break;
                                }
                                if( ((y+1) < l)
                                && !(all[x][y]&N)
                                && !(all[x][y+1]&B) )  {
                                        all[x][y] |= N;
                                        all[x][y+1] |= S;
                                        line[x*2+1][y*2+2] =  "  ";
                                        line2[x*2+1][y*2+2] = "  ";
                                        flag = 1;
                                        break;
                                }
                                if( ((y-1) >= 0)
                                && !(all[x][y]&S)
                                && !(all[x][y-1]&B) )  {
                                        all[x][y] |= S;
                                        all[x][y-1] |= N;
                                        line[x*2+1][y*2] =  "  ";
                                        line2[x*2+1][y*2] = "  ";
                                        flag = 1;
                                        break;
                                }
                        }

                        if( flag ) {
                                for( int k=0;k<sizeof(alldead[i]);k++ ) {
/*
                                        tmp2 = alldead[i][k];
                                        x = tmp2->x;
                                        y = tmp2->y;
*/
                                        x = (alldead[i][k])->x;
                                        y = (alldead[i][k])->y;
                                        all[x][y] ^= B;
                                        for( int n=0;n<sizeof(badpath);n++ ) {
                                                if( badpath[n]->x == x && badpath[n]->y == y )
                                                        badpath[n] = 0;
                                        }
                                        badpath -= ({ 0 });
                                }
                                alldead[i] = 0;
                        }
                }
                alldead -= ({ 0 });
        }

        if( sizeof(badpath) )
                log_file( "static/maze", sprintf("有%d个呆死的房间。\n",
                          sizeof(badpath)) );
}

void remove_maze()
{
        object room;
        /*
        string fname = base_name(this_object());
        int x,y;

        if( handle_id )
                SCHEDULE_D->delete_event(handle_id);

        for( x=0;x<l;x++ )
                for( y=0;y<l;y++ )
                        if( objectp(room = find_object(sprintf("%s/%d/%d",fname,x,y))) )
                                destruct(room);
        if( room = find_object(sprintf("%s/entry",fname)) )
                destruct(room);
        if( room = find_object(sprintf("%s/exit",fname)) )
                destruct(room);
        */
        if( room = find_object(sprintf("%senter.c",base_dir(this_object()))) )
                destruct(room);
        if( room = find_object(sprintf("%sleave.c",base_dir(this_object()))) )
                destruct(room);

        destruct(this_object());
}

// 设置迷宫销毁时间
void set_remove_time(int t)
{
        remove_time = time() + t;
        handle_id = SCHEDULE_D->set_event(t, 0, this_object(), "remove_maze");
}

protected void link_to_west(int x, int y)        // The west room is (x-1,y)
{
        class coordinate temp;

        // 已经到达了迷宫出口
        if( x == leave->x && y == leave->y ) {
                line[x*2+1][y*2+1] =  HBRED "  " NOR;
                line2[x*2+1][y*2+1] = HBRED "  " NOR;
                return;
        }

        temp = new(class coordinate);
        temp->x = x-1;
        temp->y = y;

        // 西面的房间已经于 path 中,或者 已在待处理列表 newpath 中.
        if( all[temp->x][temp->y]&D )
                return;

        // 迷宫入口
        if( x == enter->x && y == enter->y ) {
                line[x*2+1][y*2+1] =  HBWHT "  " NOR;
                line2[x*2+1][y*2+1] = HBWHT "  " NOR;
        } else {
                // 标上路径的颜色
                // 如果已经有颜色了，表示有宝箱或者陷阱，不再更改地图
                if( line[x*2+1][y*2+1] == "  " ) {
                        line[x*2+1][y*2+1] = BGRN "  " NOR;
                }
        }

        all[x][y] |= W;
        all[x][y] |= R;
        all[temp->x][temp->y] |= E;
        all[temp->x][temp->y] |= D;
        newpath += ({ temp });
        roadpath += ({ temp }); // 路径的房间

        line[x*2][y*2+1] = BGRN "  " NOR;
        line2[x*2][y*2+1] = "  ";
}

protected void link_to_east(int x,int y)        // The east room is (x+1,y)
{
        class coordinate temp;

        // 已经到达了迷宫出口
        if( x == leave->x && y == leave->y ) {
                line[x*2+1][y*2+1] =  HBRED "  " NOR;
                line2[x*2+1][y*2+1] = HBRED "  " NOR;
                return;
        }

        temp = new(class coordinate);
        temp->x = x+1;
        temp->y = y;

        // 东面的房间已经于 path 中,或者 已在待处理列表 newpath 中.
        if( all[temp->x][temp->y]&D )
                return;

        // 迷宫入口
        if( x == enter->x && y == enter->y ) {
                line[x*2+1][y*2+1] =  HBWHT "  " NOR;
                line2[x*2+1][y*2+1] = HBWHT "  " NOR;
        } else {
                // 如果已经有颜色了，表示有宝箱或者陷阱，不再更改地图
                if( line[x*2+1][y*2+1] == "  " ) {
                        line[x*2+1][y*2+1] = BGRN "  " NOR;
                }
        }

        all[x][y] |= E;
        all[x][y] |= R;
        all[temp->x][temp->y] |= W;
        all[temp->x][temp->y] |= D;
        newpath += ({ temp });
        roadpath += ({ temp });

        line[x*2+2][y*2+1] = BGRN "  " NOR;
        line2[x*2+2][y*2+1] = "  ";
}

protected void link_to_south(int x,int y)       // The south room is (x,y-1)
{
        class coordinate temp;

        // 已经到达了迷宫出口
        if( x == leave->x && y == leave->y ) {
                line[x*2+1][y*2+1] =  HBRED "  " NOR;
                line2[x*2+1][y*2+1] = HBRED "  " NOR;
                return;
        }

        temp = new(class coordinate);
        temp->x = x;
        temp->y = y-1;

        // 南端的房间已经于 path 中,或者 已在待处理列表 newpath 中.
        if( all[temp->x][temp->y]&D )
                return;

        // 迷宫入口
        if( x == enter->x && y == enter->y ) {
                line[x*2+1][y*2+1] =  HBWHT "  " NOR;
                line2[x*2+1][y*2+1] = HBWHT "  " NOR;
        } else {
                // 如果已经有颜色了，表示有宝箱或者陷阱，不再更改地图
                if( line[x*2+1][y*2+1] == "  " ) {
                        line[x*2+1][y*2+1] = BGRN "  " NOR;
                }
        }

        all[x][y] |= S;
        all[x][y] |= R;
        all[temp->x][temp->y] |= N;
        all[temp->x][temp->y] |= D;
        newpath += ({ temp });
        roadpath += ({ temp });

        line[x*2+1][y*2] = BGRN "  " NOR;
        line2[x*2+1][y*2] = "  ";
}

protected void link_to_north(int x,int y)       // The north room is (x,y+1)
{
        class coordinate temp;

        // 已经到达了迷宫出口
        if( x == leave->x && y == leave->y ) {
                line[x*2+1][y*2+1] =  HBRED "  " NOR;
                line2[x*2+1][y*2+1] = HBRED "  " NOR;
                return;
        }

        temp = new(class coordinate);
        temp->x = x;
        temp->y = y+1;

        // 北端的房间已经于 path 中,或者 已在待处理列表 newpath 中.
        if( all[temp->x][temp->y]&D )
                return;

        // 迷宫入口
        if( x == enter->x && y == enter->y ) {
                line[x*2+1][y*2+1] =  HBWHT "  " NOR;
                line2[x*2+1][y*2+1] = HBWHT "  " NOR;
        } else {
                // 如果已经有颜色了，表示有宝箱或者陷阱，不再更改地图
                if( line[x*2+1][y*2+1] == "  " ) {
                        line[x*2+1][y*2+1] = BGRN "  " NOR;
                }
        }

        all[x][y] |= N;
        all[x][y] |= R;
        all[temp->x][temp->y] |= S;
        all[temp->x][temp->y] |= D;
        newpath += ({ temp });
        roadpath += ({ temp });

        line[x*2+1][y*2+2] = BGRN "  " NOR;
        line2[x*2+1][y*2+2] = "  ";
}

protected void init_to_west(int x,int y)        // The west room is (x-1,y)
{
        class coordinate temp;

        temp = new(class coordinate);
        temp->x = x-1;
        temp->y = y;

        all[x][y] |= W;
        all[temp->x][temp->y] |= E;
        all[temp->x][temp->y] |= D;
        roadpath += ({ temp });

        // 处理路径地图
        line[x*2][y*2+1] =  "  ";
        line2[x*2][y*2+1] = "  ";
}

protected void init_to_east(int x,int y)        // The east room is (x+1,y)
{
        class coordinate temp;

        temp = new(class coordinate);
        temp->x = x+1;
        temp->y = y;

        all[x][y] |= E;
        all[temp->x][temp->y] |= W;
        all[temp->x][temp->y] |= D;
        roadpath += ({ temp });

        line[x*2+2][y*2+1] =  "  ";
        line2[x*2+2][y*2+1] = "  ";
}

protected void init_to_south(int x,int y)       // The south room is (x,y-1)
{
        class coordinate temp;

        temp = new(class coordinate);
        temp->x = x;
        temp->y = y-1;

        all[x][y] |= S;
        all[temp->x][temp->y] |= N;
        all[temp->x][temp->y] |= D;
        roadpath += ({ temp });

        line[x*2+1][y*2] =  "  ";
        line2[x*2+1][y*2] = "  ";
}

protected void init_to_north(int x,int y)       // The north room is (x,y+1)
{
        class coordinate temp;

        temp = new(class coordinate);
        temp->x = x;
        temp->y = y+1;

        all[x][y] |= N;
        all[temp->x][temp->y] |= S;
        all[temp->x][temp->y] |= D;
        roadpath += ({ temp });

        line[x*2+1][y*2+2] =  "  ";
        line2[x*2+1][y*2+2] = "  ";
}

protected mixed init_to_link(int x,int y)
{
        int *outs = ({});
        int dir, retn = 0;
        class coordinate temp;
        mixed result = ({});

        all[x][y] |= T;

        if( ((x-1) >= 0)
        && !(all[x][y]&W) ) {
                if( !(all[x-1][y]&T)
                && !(all[x-1][y]&B) )
                        outs += ({ W });
        }

        if( ((x+1) < l)
        && !(all[x][y]&E) ) {
                if( !(all[x+1][y]&T)
                && !(all[x+1][y]&B) )
                        outs += ({ E });
        }

        if( ((y+1) < l)
        && !(all[x][y]&N) ) {
                if( !(all[x][y+1]&T)
                && !(all[x][y+1]&B) )
                        outs += ({ N });
        }

        if( ((y-1) >= 0)
        && !(all[x][y]&S) ) {
                if( !(all[x][y-1]&T)
                && !(all[x][y-1]&B) )
                        outs += ({ S });
        }

        if( sizeof(outs) < 1 ) {
                all[x][y] ^= T;
                if( !(all[x][y]&D) ) {
                        all[x][y] |= B;
                        all[x][y] |= D;
                        temp = new(class coordinate);
                        temp->x = x;
                        temp->y = y;
                        result = ({ temp });
                        badpath += ({ temp });
                }
                return result;
        }

        dir = outs[random(sizeof(outs))];
        retn |= dir;

        if( retn&N ) {
                temp = new(class coordinate);
                temp->x = x;
                temp->y = y+1;

                all[x][y] |= N;
                all[temp->x][temp->y] |= S;

                line[x*2+1][y*2+2] =  "  ";
                line2[x*2+1][y*2+2] = "  ";
        } else
        if( retn&S ) {
                temp = new(class coordinate);
                temp->x = x;
                temp->y = y-1;

                all[x][y] |= S;
                all[temp->x][temp->y] |= N;

                line[x*2+1][y*2] =  "  ";
                line2[x*2+1][y*2] = "  ";
        } else
        if( retn&W ) {
                temp = new(class coordinate);
                temp->x = x-1;
                temp->y = y;

                all[x][y] |= W;
                all[temp->x][temp->y] |= E;

                line[x*2][y*2+1] =  "  ";
                line2[x*2][y*2+1] = "  ";
        } else
        if( retn&E ) {
                temp = new(class coordinate);
                temp->x = x+1;
                temp->y = y;

                all[x][y] |= E;
                all[temp->x][temp->y] |= W;

                line[x*2+2][y*2+1] =  "  ";
                line2[x*2+2][y*2+1] = "  ";
        }

        if( !(all[temp->x][temp->y]&D) )
                result = init_to_link(temp->x, temp->y);

        all[x][y] ^= T;
        all[x][y] |= D;
        if( sizeof(result) > 0 ) {
                all[x][y] |= B;
                temp = new(class coordinate);
                temp->x = x;
                temp->y = y;
                badpath += ({ temp });
                result +=  ({ temp });
        }

        return result;
}

// 初始化地图的处理
void init_line()
{
        int i, x, y/*, flag*/;

        line = allocate(l*2+1);  // 显示详细地图
        line2 = allocate(l*2+1); // 显示普通地图
        for( i=0;i<sizeof(line);i++ ) {
                line[i] = allocate(l*2+1);
                line2[i] = allocate(l*2+1);
        } // 建立数组

        for( y=sizeof(line)-1;y>=0;y-- ) {
                for( x=0;x<sizeof(line[y]);x++ ) {
                        if( y%2 == 1 ) {
                                if( x%2 == 1 ) {
                                        if( all[x/2][y/2]&MAP ) {         // 有地图宝箱
                                                line[x][y] = BYEL "  " NOR;
                                                line2[x][y] = "  ";
                                        } else if( all[x/2][y/2]&BOX ) {  // 宝箱
                                                line[x][y] = BYEL "  " NOR;
                                                line2[x][y] = "  ";
                                        } else if( all[x/2][y/2]&TRAP ) { // 陷阱
                                                line[x][y] = BMAG "  " NOR;
                                                line2[x][y] = "  ";
                                        } else if( all[x/2][y/2]&CENTER ) {  // 特殊房间
                                                line[x][y] = BCYN "  " NOR;
                                                line2[x][y] = "  ";
                                        } else if( all[x/2][y/2]&SPECIAL ) { // 特殊房间
                                                line[x][y] = BCYN "  " NOR;
                                                line2[x][y] = "  ";
                                        } else
                                                line[x][y] = line2[x][y] = "  ";
                                } else
                                        line[x][y] = line2[x][y] = HIG "│" NOR;
                        } else {
                                if( x%2 == 1 )
                                        line[x][y] = line2[x][y] = HIG "--" NOR;
                                else {
                                        if( y == 0 ) {
                                                if( x == 0 )
                                                        line[x][y] = line2[x][y] = HIG "└" NOR;
                                                else if( x == l*2 )
                                                        line[x][y] = line2[x][y] = HIG "┘" NOR;
                                                else
                                                        line[x][y] = line2[x][y] = HIG "┴" NOR;
                                        } else if ( y == l*2 ) {
                                                if( x == 0 )
                                                        line[x][y] = line2[x][y] = HIG "┌" NOR;
                                                else if( x == l*2 )
                                                        line[x][y] = line2[x][y] = HIG "┐" NOR;
                                                else
                                                        line[x][y] = line2[x][y] = HIG "┬" NOR;
                                        } else {
                                                if( x == 0 )
                                                        line[x][y] = line2[x][y] = HIG "├" NOR;
                                                else if( x == l*2 )
                                                        line[x][y] = line2[x][y] = HIG "┤" NOR;
                                                else
                                                        line[x][y] = line2[x][y] = HIG "┼" NOR;
                                        }
                                }
                        }
                }
        }
}

public string display_deep_map(object room)
{
        string map = "\n迷宫地图：\n" WHT "白色方块" NOR "表示迷宫入口；"
                                      RED "红色方块" NOR "表示迷宫出口；"
                                      HIB "蓝色五角星" NOR "表示你当前的位置。\n"
                                      CYN "青色方块" NOR "表示特殊房间；"
                                      YEL "黄色方块" NOR "表示有宝箱；"
                                      MAG "紫色方块" NOR "表示有陷阱。\n";
        int i, j;
        int x, y;

        if( !line )
                return "迷宫地图不存在。\n";

        if( objectp(room) ) {
                x=query("maze/x", room);
                y=query("maze/y", room);
        } else {
                x = -10;
                y = -10;
        }

        for( j=sizeof(line)-1;j>=0;j-- ) {
                for( i=0;i<sizeof(line[j]);i++ ) {
                        if( i == x*2+1 && j == y*2+1 )
                                map += replace_string(line[i][j], "  ", HIB "★" NOR);
                        else
                                map += line[i][j];
                }
                map += "\n";
        }
        return map;
}

public string display_common_map(object room)
{
        string map = "\n迷宫地图：\n" WHT "白色方块" NOR "表示迷宫入口；"
                                      RED "红色方块" NOR "表示迷宫出口；"
                                      HIB "蓝色五角星" NOR "表示你当前的位置。\n";
        int i, j;
        int x, y;

        if( map_status == MAP_NONE )
                return  "迷宫地图失效。\n";

        if( map_status == MAP_DEEP )
                return display_deep_map(room);

        if( !line2 )
                return "迷宫地图不存在。\n";

        if( objectp(room) ) {
                x=query("maze/x", room);
                y=query("maze/y", room);
        } else {
                x = -10;
                y = -10;
        }

        for( j=sizeof(line2)-1;j>=0;j-- ) {
                for( i=0;i<sizeof(line2[j]);i++ ) {
                        if( display_coordinate && i == x*2+1 && j == y*2+1 )
                                map += replace_string(line2[i][j], "  ", HIB "★" NOR);
                        else
                                map += line2[i][j];
                }
                map += "\n";
        }
        return map;
}

void init_special()
{
        int x, y, unique_num;
        class coordinate temp, *mazes = ({});

        unique_num = sizeof(unique_rooms);
        for( x=0;x<l;x++ ) {
                for( y=0;y<l;y++ ) {
                        if( x == l/2 && y == l/2 ) {
                                if( stringp(center_room) ) {
                                        all[x][y] |= CENTER;
                                        continue;
                                }
                                if( sizeof(unique_rooms) == 4 )
                                        continue;
                        }
                        if( unique_num > 0 && ((x == 0 && y == 0)
                        ||      (x == 0 && y == l-1)
                        ||      (x == l/2 && y == l/2)
                        ||      (x == l-1 && y == 0)
                        ||      (x == l-1 && y == l-1)) ) {
                                all[x][y] |= SPECIAL;
                                unique_num --;
                                continue;
                        }
                        if( (x == enter->x && y == enter->y) ||
                            (x == leave->x && y == leave->y) )
                                continue;

                        temp = new(class coordinate);
                        temp->x = x;
                        temp->y = y;
                        mazes += ({ temp });
                }
        }

        // 分布带地图宝箱
        //temp = new(class coordinate);
        temp = mazes[random(sizeof(mazes))];
        x = temp->x;
        y = temp->y;
        all[x][y] |= MAP;
        mazes -= ({ temp });

        // 分布其他的宝箱
        while( box_num > 0 ) {
                if( sizeof(mazes) < 1 )
                        break;
                //temp = new(class coordinate);
                temp = mazes[random(sizeof(mazes))];
                x = temp->x;
                y = temp->y;
                all[x][y] |= BOX;
                mazes -= ({ temp });
                box_num --;
        }

        // 分布陷阱
        while( trap_num > 0 ) {
                if( sizeof(mazes) < 1 )
                        break;
                //temp = new(class coordinate);
                temp = mazes[random(sizeof(mazes))];
                x = temp->x;
                y = temp->y;
                all[x][y] |= TRAP;
                mazes -=  ({ temp });
                trap_num --;
        }
        return;
}

// 摔跤到随机房间
public object trip_maze(object room)
{
        int x, y;
        object next;
        string fname;

        if( !objectp(room) ) return 0;

        fname = base_name(this_object());

        while( 1 ) {
                x = random(l);
                y = random(l);
                if( (x == enter->x && y == enter->y) ||
                    (x == leave->x && y == leave->y) )
                        continue;

                if( x == query("maze/x", room) &&
                    y == query("maze/y", room) )
                        continue;         // 不能是该房间本身

                if( all[x][y]&TRAP )
                        continue;

                next = load_object(sprintf("%s/%d/%d",fname,x,y));
                if( objectp(next) ) break;
        }
        return next;
}

// 拆除指定房间的陷阱
public void remove_trap(object room)
{
        int x, y;

        if( !line ) return;

        x=query("maze/x", room);
        y=query("maze/y", room);
        if( all[x][y]&R )
                line[x*2+1][y*2+1] = BGRN "  " NOR;
        else
                line[x*2+1][y*2+1] = "  ";

        return;
}

nomask int clean_up()
{
        string fname;
        int x,y;
        object room;

        if( !maze_built ) {
                destruct(this_object());
                return 0;
        }

        // 暂时取消
        return 1;

        fname = base_name(this_object());

        if( objectp(room = find_object(sprintf("%s/entry",fname))) ) {
                room->clean_up();
                if( objectp(room) )
                        return 1;
        }

        if( objectp(room = find_object(sprintf("%s/exit",fname))) ) {
                room->clean_up();
                if( objectp(room) )
                        return 1;
        }

        for( x=0;x<l;x++ )
                for( y=0;y<l;y++ )
                        if( objectp(room = find_object(sprintf("%s/%d/%d",fname,x,y))) ) {
                                //maze_objs += ({find_object(sprintf("%s/%d/%d",fname,x,y))});
                                room->clean_up();
                                if( objectp(room) )
                                        return 1;
                        }
        /*
        maze_objs->clean_up();
        maze_objs -= ({0});

        if(sizeof(maze_objs))
                return 1;
        else
        {
        */
                destruct(this_object());
                return 0;
//      }
}

void remove(string euid)
{
        string fname = base_name(this_object());
        object room;
        int x,y;

        if( handle_id )
                SCHEDULE_D->delete_event(handle_id);

        for( x=0;x<l;x++ )
                for( y=0;y<l;y++ )
                        if( objectp(room = find_object(sprintf("%s/%d/%d",fname,x,y))) )
                                destruct(room);
        if( room = find_object(sprintf("%s/entry",fname)) )
                destruct(room);
        if( room = find_object(sprintf("%s/exit",fname)) )
                destruct(room);
}

// 检查某个房间里是否有玩家。
int is_player_in(object room)
{
        object *inv;
        inv = all_inventory(room);
        for (int i = 0;i < sizeof(inv) ; i++)
                if (userp(inv[i]))
                        return 1;
        return 0;
}

int have_player_in()
{
        string fname = base_name(this_object());
        object room;
        int x,y;
        for( x=0;x<l;x++ ) {
                for( y=0;y<l;y++ ) {
                        if(objectp(room = find_object(sprintf("%s/%d/%d",fname,x,y))))
                                if (is_player_in(room))
                                        return 1;
                }
        }

        if( objectp(room = find_object(sprintf("%s/entry",fname))) )
                if (is_player_in(room))
                        return 1;
        if( objectp(room = find_object(sprintf("%s/exit",fname))) )
                if ( is_player_in(room) )
                        return 1;

        return 0;
}

object *query_maze_players()
{
        string fname = base_name(this_object());
        object *inv, *ret;
        object room;
        int x,y;
        ret = ({});
        for( x=0;x<l;x++ ) {
                for( y=0;y<l;y++ ) {
                        if( objectp(room = find_object(sprintf("%s/%d/%d",fname,x,y))) ) {
                                        inv = all_inventory(room);
                                        for( int i=0;i<sizeof(inv);i++ )
                                                if( userp(inv[i]) )
                                                        ret += ({ inv[i] });
                        }
                }
        }

        if( objectp(room = find_object(sprintf("%s/entry",fname))) ) {
                inv = all_inventory(room);
                for( int i=0;i<sizeof(inv);i++ )
                        if( userp(inv[i]) )
                                ret += ({ inv[i] });
        }
        if( objectp(room = find_object(sprintf("%s/exit",fname))) ) {
                inv = all_inventory(room);
                for( int i=0;i<sizeof(inv);i++ )
                        if( userp(inv[i]) )
                                ret += ({ inv[i] });
        }

        return ret;
}

void refresh_maze()
{
        string fname = base_name(this_object());
        object room;
        int x,y;

        if (this_object()->have_player_in()) {
                SCHEDULE_D->set_event(10, 0, this_object(), "refresh_maze");
                return;
        }

        for( x=0;x<l;x++ )
                for( y=0;y<l;y++ )
                        if(objectp(room = find_object(sprintf("%s/%d/%d",fname,x,y))))
                                destruct(room);
        if( room = find_object(sprintf("%s/entry",fname)) )
                destruct(room);
        if( room = find_object(sprintf("%s/exit",fname)) )
                destruct(room);

        // 处理迷宫特殊房间
        special_rooms = copy(unique_rooms);

        return;
}

void clear_maze_item(object user)
{
        object *inv, obj;
        inv = all_inventory(user);
        if( inv && sizeof(inv)>0 )
                foreach( obj in inv ) {
                        if( obj && query("maze_item", obj) )
                                destruct(obj);
                }
}

//      把所有玩家从迷宫里搬走。
varargs int remove_all_players(object exile_room,string remove_msg)
{
        string fname = base_name(this_object());
        object room,*inv;
        int x,y,num;

        for( x=0;x<l;x++ ) {
                for( y=0;y<l;y++ ) {
                        if( objectp(room = find_object(sprintf("%s/%d/%d",fname,x,y))) ) {
                                if( remove_msg ) tell_room(room,remove_msg);
                                inv=all_inventory(room);
                                num=sizeof(inv);
                                while( num-- ) {
                                        if( !userp(inv[num]) && !inv[num]->is_worm2() && !inv[num]->is_warcraft() ) continue;
                                        clear_maze_item(inv[num]);
                                        if( exile_room )
                                                inv[num]->move(exile_room);
                                        else
                                                inv[num]->move(VOID_OB);
                                }
                        }
                }
        }

        if( objectp(room = find_object(sprintf("%s/entry",fname))) ) {
                if( remove_msg ) tell_room(room,remove_msg);
                inv=all_inventory(room);
                num=sizeof(inv);
                while( num-- ) {
                        if( !userp(inv[num]) && !inv[num]->is_worm2() && !inv[num]->is_warcraft() ) continue;
                        clear_maze_item(inv[num]);
                        if( exile_room )
                                inv[num]->move(exile_room);
                        else
                                inv[num]->move(VOID_OB);
                }
        }

        if( objectp(room = find_object(sprintf("%s/exit",fname))) )     {
                if( remove_msg ) tell_room(room,remove_msg);
                inv=all_inventory(room);
                num=sizeof(inv);
                while( num-- ) {
                        if( !userp(inv[num]) && !inv[num]->is_worm2() && !inv[num]->is_warcraft() ) continue;
                        clear_maze_item(inv[num]);
                        if( exile_room )
                                inv[num]->move(exile_room);
                        else
                                inv[num]->move(VOID_OB);
                }
        }
}

void set_display_coor(int flag)
{
        if( !intp(flag) ) flag = 0;
        display_coordinate = flag;
}

void set_display_map(int flag)
{
        if( intp(flag) && flag>=2 )
                map_status = MAP_DEEP;
        else if( intp(flag) && flag==1 )
                map_status = MAP_COMM;
        else
                map_status = MAP_NONE;
}

void set_maze_boss(object ob)
{
        if( objectp(ob) )
                maze_boss = ob;
}

void set_boss_weakly()
{
        int i, level;
        mapping skills;
        string *ks;
        if( !objectp(maze_boss) ) return;
        if( mapp(skills = maze_boss->query_skills()) ) {
                ks = keys(skills);
                for( i=0;i<sizeof(ks);i++ ) {
                        level = skills[ks[i]]+2;
                        maze_boss->set_skill(ks[i], level/2);
                }
        }
        return;
}

/**** 以下是预设迷宫参数的接口函数 ****/
// 迷宫的单边长
void set_maze_long(int mlong)
{
        if( !intp(mlong) )
                return;

        // 最小为 5，再小了没什么意义。
        if( (mlong < 5) || mlong > MAX_LONG )
                return;

        l = mlong;
}

// 迷宫可使用的房间文件名 (****)
void set_valid_rooms(mixed room_files)
{
        if( stringp(room_files) ) {
                // 档案是否存在
                if( file_size(sprintf("%s.c",room_files)) > 0 ) {
                        object ob = find_object(room_files);

                        if( !ob )
                                ob = load_object(room_files);
                        if( ob && query("short", ob) && query("long", ob)){
                                valid_rooms = ({ room_files });
                                switch_flag = 1;
                        }
                }
                return;
        } else if( arrayp(room_files) ) {
                foreach( string f in room_files ) {
                        object ob;

                        if( !stringp(f) || f == "" )
                                return;
                        if( file_size(sprintf("%s.c",f)) <= 0 )
                                return;
                        if( !ob = find_object(f) )
                                ob = load_object(f);
                        if( !ob || !query("short", ob) || !query("long", ob) )
                                return;
                }
                valid_rooms = room_files;
                switch_flag = 1;
                return;
        }

}

// 迷宫房间所继承的物件的档案名称。
void set_inherit_room( mixed rooms )
{
        if( stringp(rooms) ) {
                // 此档案是否存在
                if( file_size(sprintf("%s.c",rooms)) > 0 )
                        inherit_rooms = ({ rooms });
                return;
        } else if( arrayp(rooms) ) {
                foreach( string f in rooms ) {
                        if( !stringp(f) || f == "" )
                                return;
                        if( file_size(sprintf("%s.c",f)) <= 0 )
                                return;
                }
                inherit_rooms = rooms;
                return;
        }

        return;
}

// 入口方向(出口在对面)
void set_entry_dir(string dir)
{
        if( !stringp(dir) )
                return;

        // 入口方向的合法性检查.
        if( member_array(dir,valid_dirs) == -1 )
                return;

        entry_dir = dir;
}

// 入口与区域的连接方向
void set_link_entry_dir(string dir)
{
        if( !stringp(dir) || dir == "" )
                return;

        link_entry_dir = dir;
}

// 迷宫入口所连接区域档案的文件名
void set_link_entry_room(string lroom)
{
        if( !stringp(lroom) || lroom == "" )
                return;

        if( file_size(sprintf("%s.c",lroom)) <= 0 )
                return;

        link_entry_room = lroom;
}

// 迷宫入口房间的坐标，我们无法用简单的方法把迷宫坐标安排在
// 进口/出口内（这个需要得到迷宫与区域的关系）
// 所以我们认为迷宫是进口区域延伸的一部分，当走出迷宫出口时，跳跃进入下一个区域。
// 缺点是，一个大迷宫的坐标可能与真实区域重叠，这个就要设计者自己留意了，
// 比如说，不要把100x100的迷宫安排在 (1,1)和 (10,10)之间。。。。自己算一下吧
void set_link_entry_room_x(int x)
{
        if( !intp(x) ) link_entry_room_x=0;
        else    link_entry_room_x = x;
}
void set_link_entry_room_y(int y)
{

        if( !intp(y) ) link_entry_room_y=0;
        else    link_entry_room_y = y;
}
void set_link_entry_room_z(int z)
{
        if( !intp(z) ) link_entry_room_z=0;
        else    link_entry_room_z = z;
}

// 出口与区域的连接方向
void set_link_exit_dir(string dir)
{
        if( !stringp(dir) || dir == "" )
                return;

        link_exit_dir = dir;
}

// 迷宫出口所连接区域档案的文件名
void set_link_exit_room(string lroom)
{
        if( !stringp(lroom) || lroom == "" )
                return;

        if( file_size(sprintf("%s.c",lroom)) <= 0 )
                return;

        link_exit_room = lroom;
}

// 迷宫入口的短描述
void set_entry_short(string desc)
{
        if( !stringp(desc) || desc == "" )
                return;

        entry_short = desc;
}

// 迷宫入口的长描述
void set_entry_desc(string desc)
{
        if( !stringp(desc) || desc == "" )
                return;

        entry_desc = desc;
}

// 迷宫出口的短描述
void set_exit_short(string desc)
{
        if( !stringp(desc) || desc == "" )
                return;

        exit_short = desc;
}

// 迷宫出口的长描述
void set_exit_desc(string desc)
{
        if( !stringp(desc) || desc == "" )
                return;

        exit_desc = desc;
}

// 迷宫房间的短描述
void set_maze_room_short(string desc)
{
        if( !stringp(desc) || desc == "" )
                return;

        maze_room_short = desc;
}

// 迷宫房间的描述，如果有多条描述，制造每个房
// 间的时候会从中随机选择一个。
void set_maze_room_desc(mixed desces)
{
        if( stringp(desces) ) {
                maze_room_desc = ({ desces });
                return;
        } else if(arrayp(desces)) {
                foreach( string desc in desces )
                        if( !stringp(desc) )
                                return;
                maze_room_desc = desces;
                return;
        }
}

// 迷宫房间是否为户外房间
void set_outdoors(int outd)
{
        if( !intp(outd) )
                return;

        if( outd )
                is_outdoors = 1;
}

// 迷宫中的怪物
void set_maze_npcs(mixed npc)
{
        if( stringp(npc) ) {
                // 此档案是否存在
                if( file_size(sprintf("%s.c",npc)) > 0 )
                        maze_npcs = ({ npc });
                return;
        } else if( arrayp(npc) ) {
                foreach( string f in npc ) {
                        if( !stringp(f) || f == "" )
                                return;
                        if( file_size(sprintf("%s.c",f)) <= 0 )
                                return;
                }
                maze_npcs = npc;
                return;
        } else if( mapp(npc) ) {
                string *ns;

                ns = keys(npc);
                foreach( string f in ns ) {
                        if( !stringp(f) || f == "" )
                                return;
                        if( file_size(sprintf("%s.c",f)) <= 0 )
                                return;
                }
                maze_npcs = npc;
                return;
        }
        return;
}

// 迷宫入口的怪物
void set_entry_npcs(mixed npc)
{
        if( stringp(npc) ) {
                // 此档案是否存在
                if( file_size(sprintf("%s.c",npc)) > 0 )
                        entry_npcs = ({ npc });
                return;
        } else if( arrayp(npc) ) {
                foreach( string f in npc ) {
                        if( !stringp(f) || f == "" )
                                return;
                        if( file_size(sprintf("%s.c",f)) <= 0 )
                                return;
                }
                entry_npcs = npc;
                return;
        } else if( mapp(npc) ) {
                string *ks;

                ks = keys(npc);
                foreach( string f in ks ) {
                        if( !stringp(f) || f == "" )
                                return;
                        if( file_size(sprintf("%s.c",f)) <= 0 )
                                return;
                }
                entry_npcs = npc;
                return;
        }
        return;
}

// 迷宫出口的怪物
void set_exit_npcs(mixed npc)
{
        if( stringp(npc) ) {
                // 此档案是否存在
                if( file_size(sprintf("%s.c",npc)) > 0 )
                        exit_npcs = ({ npc });
                return;
        } else if( arrayp(npc) ) {
                foreach( string f in npc ) {
                        if( !stringp(f) || f == "" )
                                return;
                        if( file_size(sprintf("%s.c",f)) <= 0 )
                                return;
                }
                exit_npcs = npc;
                return;
        } else if( mapp(npc) ) {
                string *ks;

                ks = keys(npc);
                foreach( string f in ks ) {
                        if( !stringp(f) || f == "" )
                                return;
                        if( file_size(sprintf("%s.c",f)) <= 0 )
                                return;
                }
                exit_npcs = npc;
                return;
        }
        return;
}

void set_unique_room(mixed room)
{
        if( stringp(room) ) {
                // 此档案是否存在
                if( file_size(sprintf("%s.c",room)) > 0 )
                        unique_rooms = ({ room });
        } else if( arrayp(room) ) {
                foreach( string f in room ) {
                        if( !stringp(f) || f == "" )
                                return;
                        if( file_size(sprintf("%s.c",f)) <= 0 )
                                return;
                }
                unique_rooms = room;
        }
        special_rooms = copy(unique_rooms);
        return;
}

void set_center_room(string room)
{
        if( !stringp(room) || room == "" )
                return;
        if( file_size(sprintf("%s.c",room)) > 0 )
                center_room = room;
        return;
}

// 迷宫宝箱的数量
void set_maze_boxs(int number)
{
        if( intp(number) && number>=1 )
                box_num = number;
}

// 迷宫陷阱的数量
void set_maze_traps(int number)
{
        if( intp(number) && number>=1 )
                trap_num = number;
}

// 迷宫刷新
void set_maze_refresh(int refresh)
{
        if( intp(refresh) && refresh>=1 )
                refresh_delay = refresh;
}

// 迷宫设计非死亡房间
void set_maze_nodeath(int flag)
{
        if( intp(flag) && flag>=1 )
                is_nodeath = flag;
}

// 迷宫中的怪物出现可能性
void set_npcs_rate(int rate)
{
        if( !intp(rate) )
                return;

        random_rate = rate;
}

void set_normal_room(int flag)
{
        if( intp(flag) && flag >= 1 )
			    normal_room = flag;
}

void set_lonely_create(int flag)
{
        if( intp(flag) && flag>=1 )
                lonely_create = flag;
}
/**** 以上是预设迷宫参数的接口函数 ****/

// 创造迷宫房间，由 VIRTUAL_D 调用。
nomask object query_maze_room(string str)
{
        int idx,x,y,exits;
        int box_type,trap_type;
        object ob,obj;
        string f;
        int unique_flag;

        /*
        if( previous_object() && (geteuid(previous_object()) != ROOT_UID) )
                return 0;
        */

        if( !stringp(str) || str == "" )
                return 0;

        if( !maze_built ) // 迷宫未建立
                create_maze();
        if( !maze_built )
                return 0;

        if( !random_rate )
                random_rate = 50; // 房间内放置 npc 的可能性

        if( str == "entry" ) {     // 迷宫入口房间
                f = inherit_rooms[random(sizeof(inherit_rooms))];
                ob = new(f);
                //ob = load_object(f);
                if( !ob )
                        return 0;
                set("short", entry_short, ob);
                set("long", entry_desc, ob);
                set("maze", 1, ob);
                set("no_magic", 1, ob);
                set("virtual_room", 1, ob);
                if( is_outdoors )
                        set("outdoors", 1, ob);
                if( is_nodeath )
                        set("no_death", 1, ob);
                if( link_entry_room ) set(sprintf("exits/%s",link_entry_dir),link_entry_room,ob);
                set(sprintf("exits/%s",reverse_dir[entry_dir]),mroom_fname(enter->x,enter->y), ob);
                set("coor/x", link_entry_room_x, ob);
                set("coor/y", link_entry_room_y, ob);
                set("coor/z", link_entry_room_z, ob);
                set("mazeobj", base_name(this_object()), ob);
                set("maze/x", enter->x, ob);
                set("maze/y", enter->y, ob);
                if( arrayp(entry_npcs) && sizeof(entry_npcs) ) {
                        set("objects",([
                                entry_npcs[random(sizeof(entry_npcs))] : 1,
                        ]), ob);
                        ob->setup();
                } else if( mapp(entry_npcs) && sizeof(entry_npcs) ) {
                        set("objects", entry_npcs, ob);
                        ob->setup();
                }

                return ob;
        }

        if( str == "exit" ) {      // 迷宫出口房间
                f = inherit_rooms[random(sizeof(inherit_rooms))];
                ob = new(f);
                //ob = load_object(f);
                if( !ob )
                        return 0;

                set("short", exit_short, ob);
                set("long", exit_desc, ob);
                set("maze", 1, ob);
                set("no_magic", 1, ob);
                set("virtual_room", 1, ob);
                if( is_outdoors )
                        set("outdoors", 1, ob);
                if( is_nodeath )
                        set("no_death", 1, ob);
                if( link_exit_room ) set(sprintf("exits/%s",link_exit_dir),link_exit_room,ob);
                set(sprintf("exits/%s",entry_dir),mroom_fname(leave->x,leave->y),ob);
                set("mazeobj", base_name(this_object()), ob);
                set("maze/x", leave->x, ob);
                set("maze/y", leave->y, ob);
                if( arrayp(exit_npcs) && sizeof(exit_npcs) ) {
                        set("objects",([
                                exit_npcs[random(sizeof(exit_npcs))] : 1,
                        ]), ob);
                        ob->setup();
                } else if( mapp(exit_npcs) && sizeof(exit_npcs) ) {
                        set("objects", exit_npcs, ob);
                        ob->setup();
                }

                return ob;
        }

        idx = member_array('/', str);
        if( idx == -1 )
                return 0;

        if( !sscanf(str[0..idx-1],"%d",x) )
                return 0;
        if( !sscanf(str[idx+1..],"%d",y) )
                return 0;

        if( !exits = all[x][y] )
                return 0;

        // 处理unique rooms4个角落，和中心位置
        unique_flag = 0;
        if( exits&SPECIAL && sizeof(special_rooms) > 0 ) {
                unique_flag = 1;
                f = special_rooms[random(sizeof(special_rooms))];
                special_rooms -= ({ f });
        } else if( exits&CENTER ) {
                unique_flag = 1;
                f = center_room;
        } else if( exits&TRAP ) {
                f = TRAP_ROOM;
        } else {
                // 不同的创建方法
                if( switch_flag )
                        f = valid_rooms[random(sizeof(valid_rooms))];
                else
                        f = inherit_rooms[random(sizeof(inherit_rooms))];
        }

        ob = new(f);
        //ob = load_object(f);
        if( !ob )
                return 0;

        if( !switch_flag && !unique_flag ) {
                set("short", maze_room_short, ob);
                set("long", maze_room_desc[random(sizeof(maze_room_desc))], ob);
                set("maze", 1, ob);
                set("no_magic", 1, ob);
                set("virtual_room", 1, ob);
                if( is_outdoors )
                        set("outdoors", 1, ob);
                if( is_nodeath )
                        set("no_death", 1, ob);
        }

        if( exits&TRAP ) {
                trap_type = random(100);
                if( trap_type > 97 )
                        set("maze/trap", LOSTMAP, ob);//百分之一十
                else if( trap_type < 20 )
                        set("maze/trap", TRIP, ob);//百分之二十
                else if( trap_type < 40 )
                        set("maze/trap", CHANGEMAP, ob);//百分之四十
                else if (trap_type < 70)
                        set("maze/trap", WOUND, ob);//百分之七十
                else
                        set("maze/trap", BUSY, ob);
        }

        // 根据入口坐标和迷宫大小来定义房间坐标
        set("coor/x", x*10-l+link_entry_room_x, ob);
        set("coor/y", y*10-to_int(l/2)+link_entry_room_y, ob);
        set("coor/z", link_entry_room_z, ob);
        set("mazeobj", base_name(this_object()), ob);
        set("maze/x", x, ob);
        set("maze/y", y, ob);

        if( exits&W )
                set("exits/west", mroom_fname(x-1,y), ob);
        else if( !normal_room )
                set("exits/west", mroom_fname(x,y), ob);
        if( exits&E )
                set("exits/east", mroom_fname(x+1,y), ob);
        else if( !normal_room )
                set("exits/east", mroom_fname(x,y), ob);
        if( exits&N )
                set("exits/north", mroom_fname(x,y+1), ob);
        else if( !normal_room )
                set("exits/north", mroom_fname(x,y), ob);
        if( exits&S )
                set("exits/south", mroom_fname(x,y-1), ob);
        else if( !normal_room )
                set("exits/south", mroom_fname(x,y), ob);

        if( (x == enter->x) && (y == enter->y) )
                set(sprintf("exits/%s",entry_dir),
                        sprintf("%s/entry",base_name(this_object())), ob);
        if( (x == leave->x) && (y == leave->y) )
                set(sprintf("exits/%s",reverse_dir[entry_dir]),
                        sprintf("%s/exit",base_name(this_object())), ob);

        if( !switch_flag && !unique_flag ) {
                if( mapp(maze_npcs) && sizeof(maze_npcs) && (random(100) <= random_rate) ) {
                        set("objects", maze_npcs, ob);
                        ob->setup();
                } else if( arrayp(maze_npcs) && sizeof(maze_npcs) && (random(100) <= random_rate) ) {
                        set("objects",([
                                maze_npcs[random(sizeof(maze_npcs))] : 1,
                        ]), ob);
                        ob->setup();
                }
        }

        if( exits&MAP ) {
                obj = new(BOX_OB);
                set("maze/box", SPECIAL_MAP, obj);
                obj->move(ob);
        } else if( exits&BOX ) {
                obj = new(BOX_OB);
                box_type = random(100);
                if( box_type > 97 )
                        set("maze/box", SPECIAL_DAN, obj);//百分之二
                else if( box_type > 94 )
                        set("maze/box", JINKUAI, obj);//百分之三
                else if( box_type < 15 )
                        set("maze/box", GOLD, obj);//百分之十五
                else if( box_type < 65 )
                        set("maze/box", OBJ, obj);//百分之五十
                else if( box_type < 85 )
                        set("maze/box", SPECIAL_OBJ, obj);//百分之二十
                else {
                        if( objectp(maze_boss) )
                                set("maze/box", NPC_SKILL, obj);
                        else
                                set("maze/box", SPECIAL_OBJ, obj);//百分之十
                }

                obj->move(ob);
        }

        return ob;
}