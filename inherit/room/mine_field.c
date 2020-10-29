/************************************************
 * mine_field.c                                 *
 *                                              *
 * 矿场                                         *
 ************************************************/

/*
1。是否有出口
2。单边长
3。含矿种类
4。总蕴藏量
5。开采几率
6。矿石中有效矿物的含量比例
7。再生期
8，矿石物件
9。矿眼房间
10。非矿眼房间
以后可以允许帮派竞买矿长的开采权
*/

// #pragma optimize

#define N                8
#define S                4
#define W                2
#define E                1
#define ALL                15

#define MAX_LONG        40
#define MIN_CONTAIN_PERSENT        5
#define MAX_CONTAIN_PERSENT        30

#define TWO_VALID_LEAVES

#include <mine_def.h>

inherit F_SAVE;
inherit F_NATURE;

class coordinate{ int x; int y; }

protected nosave class coordinate *newpath = ({});        // 待处理队列

protected nosave string *valid_dirs = ({ "south","north","west","east" });
protected nosave mapping reverse_dir = ([
"north" : "south",
"south" : "north",
"west"  : "east",
"east"  : "west",
]);

// 一些可储存的变量
protected int maze_built = 0;        // 建立标记
protected mixed *all;                // 全迷宫出口阵列.
protected class coordinate enter;        // 入口坐标
protected class coordinate leave;        // 出口坐标
protected class coordinate *mine_room_positions;        // 矿眼分布
protected int out_mine;                // 已开采的量
protected int built_time;        // 最后一次的更新时间

/***************** 矿场的一些预设特性：*****************/
protected nosave int l;                                // 单边长
protected nosave string entry_dir;                // 入口方向
protected nosave string link_entry_dir;                // 入口与区域的连接方向
protected nosave string link_entry_room;        // 入口所连接区域档案的文件名
protected nosave string link_exit_dir;                // 出口与区域的连接方向
protected nosave string link_exit_room;                // 出口所连接区域档案的文件名
protected nosave string mine_room;                // 有矿房间
protected nosave string no_mine_room;                // 无矿房间
protected nosave string mine_class;                // 矿藏种类
protected nosave int contain_persent;                // 矿石中有效矿物的含量比例
protected nosave int contain_quantity;                // 初始总蕴藏量
protected nosave int reset_time_sect;                // 矿场再生期（单位：Game年）
protected nosave int is_outdoors = 0;
/******************* ---- END ---- *********************/

// 重置全域变量.
protected void refresh_vars();

// 建立矿场地图
protected void create_maze();

// 选择随机出口.
protected int random_out(int x,int y,int n);

// 处理连接.
protected void link_to_north(int x,int y);
protected void link_to_south(int x,int y);
protected void link_to_west(int x,int y);
protected void link_to_east(int x,int y);

protected string mroom_fname(int x,int y)
{ return sprintf("%s/%d/%d",base_name(this_object()),x,y);}

string query_save_file() { return base_name(this_object()); }

protected void refresh_vars() // 重置全域变量.
{
        newpath = ({});
        all = 0;
        maze_built = 0;
}

// 对一些必设参数的合法性检查
protected int check_vars()
{
        if( (l < 10) || (l > MAX_LONG) )
                return 0;

        if(!stringp(link_entry_room)
        || !sizeof(link_entry_room)
        || (file_size(link_entry_room + ".c") <= 0) )
                return 0;

        if(!stringp(mine_room)
        || !sizeof(mine_room)
        || (file_size(mine_room + ".c") <= 0) )
                return 0;

        if(!stringp(no_mine_room)
        || !sizeof(no_mine_room)
        || (file_size(no_mine_room + ".c") <= 0) )
                return 0;

/*
        if(!stringp(mine_stone)
        || !sizeof(mine_stone)
        || (file_size(mine_stone + ".c") <= 0) )
                return 0;
*/
        if(!intp(contain_quantity) || (contain_quantity <= 0))
                return 0;

        if(!intp(contain_persent) || (contain_persent <= 0))
                return 0;

        return 1;
}

protected int random_out(int x,int y,int n) // 选择随机出口函数.
{
        int *outs = ({}), retn = 0;
        class coordinate temp;

        // The west room is (x-1,y)
        if( n&W
        && ((x-1) >= 0)
        && !all[x-1][y] )
        {
                temp = new(class coordinate);
                temp->x = x-1;
                temp->y = y;
                outs += ({ W });
        }

        // The east room is (x+1,y)
        if( n&E
        && ((x+1) < l)
        && !all[x+1][y] )
        {
                temp = new(class coordinate);
                temp->x = x+1;
                temp->y = y;
                outs += ({ E });
        }

        // The south room is (x,y-1)
        if( n&S
        && ((y-1) >= 0)
        && !all[x][y-1] )
        {
                temp = new(class coordinate);
                temp->x = x;
                temp->y = y-1;
                outs += ({ S });
        }

        // The north room is (x,y+1)
        if( n&N
        && ((y+1) < l)
        && !all[x][y+1] )
        {
                temp = new(class coordinate);
                temp->x = x;
                temp->y = y+1;
                outs += ({ N });
        }

#ifdef TWO_VALID_LEAVES
        // 如果有三个出口,随机关闭一个.
        if(sizeof(outs) >= 3)
                outs -= ({ outs[random(sizeof(outs))] });
#endif

        for(int i=0;i<sizeof(outs);i++)
                retn |= outs[i];

        return retn;
}


// 矿眼分布密度监测
protected int valid_mine_position(int x, int y)
{
        int n;

        if(!all[x][y])        // 没出口
                return 0;

        if(!n = sizeof(mine_room_positions))
                return 1;

        for(int i=0; i<n; i++)
        {
                //if( abs( (mine_room_positions[i]->x - x) * (mine_room_positions[i]->y - y) ) < 40)
                if((mine_room_positions[i]->x == x) && (mine_room_positions[i]->y == y))
                        return 0;
        }

        return 1;
}

// 创建矿眼分布阵列
protected void create_mine_room()
{
        int num, x, y;

        num = l*l/30;

        if(num < 1)
                num = 1;

        do
        {
                class coordinate tmp;

                x = random(l-3) + 1;
                y = random(l-3) + 1;

                if(!valid_mine_position(x,y))
                        continue;
                tmp = new(class coordinate);
                tmp->x = x;
                tmp->y = y;

                if(!mine_room_positions || !sizeof(mine_room_positions))
                        mine_room_positions = ({ tmp });
                else
                        mine_room_positions += ({ tmp });
        }
        while(sizeof(mine_room_positions) < num);
}

void start_heart_beat()
{
        // 每天(MUD单位)心跳一次
        set_heart_beat(120);
}

protected void create_maze()
{
        int i;
        class coordinate *valid_leaves=({}),temp;

        refresh_vars(); // 重置全域变量.
        if( !check_vars() )   // 对一些预设变量进行检查。
                return;

        // 单边长.
        all = allocate(l);
        for(i=0;i<l;i++)
                all[i] = allocate(l);        // 建立数组.

        enter = new(class coordinate);

        switch (entry_dir)
        {
                case "south":
                        // enter 入口坐标.
                        enter->x = to_int(l/2); // 取中迷宫比较平衡。
                        enter->y = 0;
                        all[enter->x][enter->y] |= S;
                        break;
                case "north":
                        enter->x = to_int(l/2);
                        enter->y = l-1;
                        all[enter->x][enter->y] |= N;
                        break;
                case "west":
                        enter->y = to_int(l/2);
                        enter->x = 0;
                        all[enter->x][enter->y] |= W;
                        break;
                case "east":
                        enter->y = to_int(l/2);
                        enter->x = l-1;
                        all[enter->x][enter->y] |= E;
                        break;
        }

        // 存入待处理队列.
        newpath += ({ enter });

        // 进入主循环.
        do
        {
                int x,y,out,numb;

                // 进行一些监测与初始化.
                if( !(numb=sizeof(newpath)) )
                        continue;
                numb = random(numb);
                reset_eval_cost();
                x = newpath[numb]->x;
                y = newpath[numb]->y;

                // 如果有三个可能的出口随机关闭一个出口:
                out = ALL^(all[x][y]);
                out = random_out(x,y,out);

                if(!out) // 没有可能的出口了.
                {
                        newpath -= ({ newpath[numb] });
                        continue;
                }

                // 处理连接.
                if(out&W) link_to_west(x,y);
                if(out&E) link_to_east(x,y);
                if(out&N) link_to_north(x,y);
                if(out&S) link_to_south(x,y);

                // 当前房间处理完毕.
                newpath -= ({ newpath[numb] });
        }
        while (sizeof(newpath));

        switch (entry_dir)
        {
                case "west":
                        for(i=0;i<l;i++)
                                if(all[l-1][i])
                                {
                                        temp = new(class coordinate);
                                        temp->x = l-1;
                                        temp->y = i;
                                        valid_leaves += ({temp});
                                }
                        break;
                case "east":
                        for(i=0;i<l;i++)
                                if(all[0][i])
                                {
                                        temp = new(class coordinate);
                                        temp->x = 0;
                                        temp->y = i;
                                        valid_leaves += ({temp});
                                }
                        break;
                case "south":
                        for(i=0;i<l;i++)
                                if(all[i][l-1])
                                {
                                        temp = new(class coordinate);
                                        temp->x = i;
                                        temp->y = l-1;
                                        valid_leaves += ({temp});
                                }
                        break;
                case "north":
                        for(i=0;i<l;i++)
                                if(all[i][0])
                                {
                                        temp = new(class coordinate);
                                        temp->x = i;
                                        temp->y = 0;
                                        valid_leaves += ({temp});
                                }
                        break;
        }

        if( !(i=sizeof(valid_leaves)) ) // 未到达对方边界
        {
                call_other(this_object(),"create_maze");
                return;
        }


        if(stringp(link_exit_room)
        && sizeof(link_exit_room)
        && (file_size(link_exit_room + ".c") > 0) )
        {
                if(i == 1)
                        leave = valid_leaves[0];
                else
                        leave = valid_leaves[random(i)]; // 随机选一个.

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
        }

        create_mine_room();

        maze_built = 1;
        //built_time = query_year()*12 + query_month();
        built_time = time();
        start_heart_beat();
        save();
}

protected void link_to_west(int x,int y)        // The west room is (x-1,y)
{
        class coordinate temp;
        // can't link. 当前房间已经是最西面的房间了.
        if( (x-1) < 0 )
                return;

        temp = new(class coordinate);
        temp->x = x-1;
        temp->y = y;

        // 西面的房间已经于 path 中,或者 已在待处理列表 newpath 中.
        if(all[temp->x][temp->y] /*|| member_array(temp,newpath)*/)
                return;

        all[x][y] |= W;
        all[temp->x][temp->y] |= E;
        newpath += ({temp});
}

protected void link_to_east(int x,int y)        // The east room is (x+1,y)
{
        class coordinate temp;
        // can't link. 当前房间已经是最东面的房间了.
        if( (x+1) >= l )
                return;

        temp = new(class coordinate);
        temp->x = x+1;
        temp->y = y;

        // 东面的房间已经于 path 中,或者 已在待处理列表 newpath 中.
        if(all[temp->x][temp->y] /*|| member_array(temp,newpath)*/)
                return;

        all[x][y] |= E;
        all[temp->x][temp->y] |= W;
        newpath += ({temp});
}

protected void link_to_south(int x,int y)        // The south room is (x,y-1)
{
        class coordinate temp;
        // can't link. 当前房间已经是最南端的房间了.
        if( (y-1) <0 )
                return;

        temp = new(class coordinate);
        temp->x = x;
        temp->y = y-1;

        // 南端的房间已经于 path 中,或者 已在待处理列表 newpath 中.
        if(all[temp->x][temp->y] /*|| member_array(temp,newpath)*/)
                return;

        all[x][y] |= S;
        all[temp->x][temp->y] |= N;
        newpath += ({temp});
}

protected void link_to_north(int x,int y)        // The north room is (x,y+1)
{
        class coordinate temp;
        // can't link. 当前房间已经是最北端的房间了.
        if( (y+1) >= l )
                return;

        temp = new(class coordinate);
        temp->x = x;
        temp->y = y+1;

        // 北端的房间已经于 path 中,或者 已在待处理列表 newpath 中.
        if(all[temp->x][temp->y] /*|| member_array(temp,newpath)*/)
                return;

        all[x][y] |= N;
        all[temp->x][temp->y] |= S;
        newpath += ({temp});
}

void remove(string euid)
{
        string fname = base_name(this_object());
        object m_room;
        int x,y;

        for(x=0;x<l;x++)
                for(y=0;y<l;y++)
                        if(objectp(m_room = find_object(sprintf("%s/%d/%d",fname,x,y))))
                                destruct(m_room);
        if(m_room = find_object(sprintf("%s/entry",fname)))
                destruct(m_room);
        if(m_room = find_object(sprintf("%s/exit",fname)))
                destruct(m_room);
}

/**** 以下是预设参数的接口函数 ****/
// 单边长
void set_maze_long(int mlong)
{
        if(!intp(mlong))
                return;

        // 最小为 10
        if( (mlong < 10) || (mlong > MAX_LONG) )
                return;

        l = mlong;
}

// 矿眼房间文件名
void set_mine_room(string room_files)
{
        object ob;

        if(!stringp(room_files) || !sizeof(room_files))
                error("set_mine_room: 参数必须为 string 类型\n");

        if(file_size(sprintf("%s.c",room_files)) <= 0)
                error("set_mine_room: 参数指定的房间文件不存在，或者无权读取\n");

        if( !objectp(ob = find_object(room_files)) )
                ob = load_object(room_files);
        if(!objectp(ob))
                error("set_mine_room: 参数指定的房间无法载入\n");
        mine_room = room_files;
}

// 非矿眼房间文件名
void set_no_mine_room(string room_files)
{
        object ob;

        if(!stringp(room_files) || !sizeof(room_files))
                error("set_no_mine_room: 参数必须为 string 类型\n");

                // 档案是否存在
        if(file_size(sprintf("%s.c",room_files)) <= 0)
                error("set_no_mine_room: 参数指定的房间文件不存在，或者无权读取\n");

        if( !objectp(ob = find_object(room_files)) )
                ob = load_object(room_files);
        if(!objectp(ob))
                error("set_no_mine_room: 参数指定的房间无法载入\n");
        no_mine_room = room_files;
}

// 设定初始总蕴藏量
void set_contain_quantity(int num)
{
        if(!intp(num) || (num <= 0))
                error("set_contain_quantity: 设定参数错误\n");
        contain_quantity = num;
}

// 设定蕴藏比例
void set_contain_persent(int num)
{
        if(!intp(num)
        || (num < MIN_CONTAIN_PERSENT)
        || (num > MAX_CONTAIN_PERSENT) )
                error("set_contain_persent: 参数设定错误\n");

        contain_persent = num;
}

// 设定矿产再生期
void set_reset_time_sect(int num)
{
        if(!intp(num) || (num <= 0))
                error("set_reset_time_sect: 参数设定错误\n");

        reset_time_sect = num;
}

void set_mine_class(string mclass)
{
        if(!stringp(mclass) || !sizeof(mclass))
                error("set_mine_class: 参数设定错误\n");
        mine_class = mclass;
}

// 入口方向(出口在对面)
void set_entry_dir(string dir)
{
        if(!stringp(dir))
                return;

        // 入口方向的合法性检查.
        if(member_array(dir,valid_dirs) == -1)
                return;

        entry_dir = dir;
}

//入口与区域的连接方向
void set_link_entry_dir(string dir)
{
        if(!stringp(dir) || dir == "")
                return;

        link_entry_dir = dir;
}

// 入口所连接区域档案的文件名
void set_link_entry_room(string room_files)
{
        object ob;

        if(!stringp(room_files) || !sizeof(room_files))
                error("set_link_entry_room: 参数必须为 string 类型\n");

                // 档案是否存在
        if(file_size(sprintf("%s.c",room_files)) <= 0)
                error("set_link_entry_room: 参数指定的房间文件不存在，或者无权读取\n");

        if( !objectp(ob = find_object(room_files)) )
                ob = load_object(room_files);
        if(!objectp(ob))
                error("set_link_entry_room: 参数指定的房间无法载入\n");
        link_entry_room = room_files;
}

//出口与区域的连接方向
void set_link_exit_dir(string dir)
{
        if(!stringp(dir) || dir == "")
                return;

        link_exit_dir = dir;
}

// 迷宫出口所连接区域档案的文件名
void set_link_exit_room(string room_files)
{
        object ob;

        if(!stringp(room_files) || !sizeof(room_files))
                error("set_link_exit_room: 参数必须为 string 类型\n");

                // 档案是否存在
        if(file_size(sprintf("%s.c",room_files)) <= 0)
                error("set_link_exit_room: 参数指定的房间文件不存在，或者无权读取\n");

        if( !objectp(ob = find_object(room_files)) )
                ob = load_object(room_files);
        if(!objectp(ob))
                error("set_link_exit_room: 参数指定的房间无法载入\n");

        link_exit_room = room_files;
}

void set_outdoors(int outd)
{
        if( !intp(outd) )
                return;

        if( outd )
                is_outdoors = 1;
}

/**** 以上是预设参数的接口函数 ****/

// 由 VIRTUAL_D 调用创造房间。
nomask object query_maze_room(string str)
{
        int idx,x,y,exits, n;
        object ob;

        if( previous_object() && (geteuid(previous_object()) != ROOT_UID) )
                return 0;

        if(!stringp(str) || str == "")
                return 0;

        if(!maze_built)
        {
                restore();
                if(!maze_built)
                        create_maze();
        }

        if(!maze_built)
                return 0;

        if(str == "entry")        // 入口为非矿眼房间
        {
                ob = new(no_mine_room);
                if(!ob)
                        return 0;

                set("no_magic", 1, ob);
                if( is_outdoors )
                        set("outdoors", 1, ob);
                set(sprintf("exits/%s", link_entry_dir),link_entry_room, ob);
                set(sprintf("exits/%s", reverse_dir[entry_dir]),mroom_fname(enter->x,enter->y), ob);

                return ob;
        }

        if(str == "exit")        // 出口为非矿眼房间
        {
                if(!leave || !link_exit_room || !sizeof(link_exit_room))
                        return 0;

                ob = new(no_mine_room);
                if(!ob)
                        return 0;
                set("no_magic", 1, ob);
                if( is_outdoors )
                        set("outdoors", 1, ob);
                set(sprintf("exits/%s", link_exit_dir),link_exit_room, ob);
                set(sprintf("exits/%s",entry_dir),
                        mroom_fname(leave->x,leave->y), ob);
                return ob;
        }

        idx = member_array('/', str);
        if( idx == -1 )
                return 0;

        if(!sscanf(str[0..idx-1],"%d",x))
                return 0;
        if(!sscanf(str[idx+1..],"%d",y))
                return 0;

        if( !exits = all[x][y] )
                return 0;

        n = sizeof(mine_room_positions);
        for(int i=0;i<n;i++)
        {
                if( (x == mine_room_positions[i]->x)
                && (y == mine_room_positions[i]->y) )
                {
                        ob = new(mine_room);
                        break;
                }
        }

        if(!ob)
                ob = new(no_mine_room);
        if(!ob)
                return 0;

        set("no_magic", 1, ob);
        if( is_outdoors )
                set("outdoors", 1, ob);
        if(exits&W)
                set("exits/west", mroom_fname(x-1,y), ob);
        if(exits&E)
                set("exits/east", mroom_fname(x+1,y), ob);
        if(exits&N)
                set("exits/north", mroom_fname(x,y+1), ob);
        if(exits&S)
                set("exits/south", mroom_fname(x,y-1), ob);

        if( (x == enter->x) && (y == enter->y) )
                set(sprintf("exits/%s",entry_dir),
                        sprintf("%s/entry",base_name(this_object())), ob);


        if( classp(leave) && (x == leave->x) && (y == leave->y) )
                set(sprintf("exits/%s",reverse_dir[entry_dir]),
                        sprintf("%s/exit",base_name(this_object())), ob);

        return ob;
}

void setup_stone(object stone)
{
        int w;

        if(!maze_built
        || !stone
        || !stone->is_mine_stone()
        || (out_mine >= contain_quantity) )
                return;

        if(!w = stone->query_weight()/100*contain_persent/100)
                return;

        stone->set_mine_class(mine_class);

        w = w*7/10 + random(w*3/10);
        if(w < 1)
                w = 1;

        out_mine += w;        // 记录已开采量

        stone->set_eff_weight(w);
}


protected void reset_mine_field()
{
        out_mine = 0;
        save();
}

/*
void reset()
{
        int tm;

        if(!maze_built)
                return;

        save();

        if(built_time <= 0)
        {
                built_time = query_year()*12 + query_month();
                return;
        }
        tm = query_year()*12 + query_month();

        if((tm - built_time) > (reset_time_sect*12))
                reset_mine_field();
}
*/

void heart_beat()
{
        int tm;

        if(!maze_built)
        {
                set_heart_beat(0);
                return;
        }


        if(built_time <= 0)
        {
                built_time = time();
                return;
        }
        tm = time();

        if((tm - built_time) > reset_time_sect*120)
                reset_mine_field();
}
