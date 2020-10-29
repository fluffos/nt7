// written by super@mudbuilder.net

#include "gls.h"
#include <socket_err.h>

#include <net/config.h>

#include <net/daemons.h>

#include <net/dns.h>

#include <net/socket.h>

#include <net/services.h>

#include <net/macros.h>

private object* find_path(object ob,object* rooms);
private void clean_path(object* rooms);
mapping all_rooms;
mixed map;
int total;
private void build_matrix(object room, string t, int x, int y, string direction);
int max_x,max_y,min_x,min_y,udp_socket;
private void check_x_y(int x, int y);
private mapping draw_map(object ob);
private int send_msg(string msg);
private mixed drawing(mapping a);
private int abs(int a) { return a>0?a:-a; }
void out(mapping a);

void create()
{
    mixed result;
    object center;
        total = 0;
    center = find_object(CENTER_OB)?
        find_object(CENTER_OB):
        load_object(CENTER_OB);
        all_rooms = ([]);
        max_x = max_y = 0;
    result = draw_map(center);
    map = drawing(result);
        out(map);
}

void out(mixed matrix)
{
        string result;
        result = "";
        for(int i = 0;i<max_x - min_x+1;i++)
    {
        for(int j = 0;j<max_y - min_y+1;j++)
            result += sprintf("%d ",matrix[j][i]);
        result += "\n";
    }
        write(replace_string(result,"0"," "));
        write(sprintf("\nTotal rooms: %d ",total));
}

private mixed drawing(mapping a)
{
    mixed *matrix;
    array kid;
    string result;
    kid = keys(a);
    result = "";
    matrix = allocate(max_x - min_x +1 );
    for(int i = 0;i<sizeof(matrix);i++)
        matrix[i] = allocate(max_y - min_y + 1);
    foreach( string name in kid )
    {
        int t1,t2;
        t1 = a[name][X] + max_x;
        t2 = abs(a[name][Y] - max_y);
        matrix[t1][t2] = 1;
        for(int i = 0;i<a[name][EXIT_SIZE];i++)
        {
            switch(a[name][EXIT(i)])
            {
                case "south" : 
                    if(undefinedp(matrix[t1][t2+1]) || !matrix[t1][t2+1]) matrix[t1][t2+1] = 2;
                    break;
                case "north" :
                    if(undefinedp(matrix[t1][t2-1]) || !matrix[t1][t2-1]) matrix[t1][t2-1] = 2;
                    break;
                case "west" :
                    if(undefinedp(matrix[t1-1][t2]) || !matrix[t1-1][t2]) matrix[t1-1][t2] = 2;
                    break;
                case "east" :
                    if(undefinedp(matrix[t1+1][t2]) || !matrix[t1+1][t2]) matrix[t1+1][t2] = 2;
                    break;
            }
        }
    }
    return matrix;
}

private mapping draw_map(object ob)
{
    object env,*temp,*temp1,*bak_room,*temp2;
    mapping exits;
    mixed n;
    int t,x,y;
    int a = 0;
    t = 0;
    env = ob;
    env->set_temp("x",0);
    env->set_temp("y",0);
    x = y = 0;
    temp = ({env});
    temp1 = ({});
    exits = env->query("exits");
    bak_room = ({env});
        
    while ( sizeof(temp) ) 
    {
        reset_eval_cost();
        temp2 = copy(temp);
        temp = ({});
                
        foreach(object room in temp2)
        {
            int size;
            exits = room->query("exits");
            x = room->query_temp("x");
            y = room->query_temp("y");
                        
            foreach(string key in keys(exits))
            {
                object _temp;
                _temp = find_object(exits[key])?
                    find_object(exits[key]):
                    load_object(exits[key]);
                                
                build_matrix(_temp, file_name(_temp), x, y, key);
                total ++;
                                temp1 += ({ _temp });
            }
            size = sizeof(temp1);
            for(int i=0;i<size;i++)
            {   
                object* new_temp = copy(temp1[i]);
                if ( sizeof(({new_temp}) & bak_room) ) {
                    temp1[i] = 0;
                }
            }
                    temp1 = filter(temp1,(: $1 != 0 :));
            bak_room += temp1;
            temp += temp1;
                        temp1 = ({});
        } 
        a++;
    } 
    return all_rooms;
}

private void build_matrix(object room, string t, int x, int y, string direction)
{
    int exit_size,num_players,buf_size;
    object *players;
        
    switch (direction)
    {
        case "north"    : y += 2;           break;
        case "south"    : y -= 2;           break;
        case "west"         : x -= 2;           break;
        case "east"         : x += 2;           break;
        case "northwest": y += 1;x -= 1;    break;
        case "northeast": y += 1;x += 1;    break;
        case "southwest": y -= 1;x -= 1;    break;
        case "southeast": y -= 1;x += 1;    break;
        default : ;
    }
    check_x_y(x,y);
    room->set_temp("x",x);
    room->set_temp("y",y);
    exit_size = sizeof(room->query("exits"));
    players = filter(all_inventory(room),(: interactive($1) :));
    num_players = sizeof(players);

    buf_size = exit_size + num_players + 4;
    all_rooms[t] = allocate(buf_size);

    all_rooms[t][X]     = x;
    all_rooms[t][Y]     = y;
    all_rooms[t][EXIT_SIZE] = exit_size;
                                
    for(int i = 0;i<all_rooms[t][EXIT_SIZE];i++)
        all_rooms[t][EXIT(i)] = keys(room->query("exits"))[i];
                                
    all_rooms[t][NUM_PLAYER(t)] = num_players;
    for(int i = 0;i<all_rooms[t][NUM_PLAYER(t)];i++)
        all_rooms[t][PLAYER(t,i)] = players[i];
}

private object* find_path(object ob,object* rooms)
{
    object *temp1;
    object temp = copy(ob);
    temp1 = ({});
        
    while(temp)
    {
        object _temp;
        temp1 += ({temp});
        _temp = temp;
        temp = temp->query_temp("father");
        _temp->delete_temp("father");
    }
        
    clean_path(rooms);
    return temp1;
}

private void clean_path(object* rooms)
{
    foreach(object room in rooms)
        room->delete_temp("father");
}

private void check_x_y(int a,int b)
{
    if(a > max_x) max_x = a;
    if(b > max_y) max_y = b;
    if(a < min_x) min_x = a;
    if(b < min_y) min_y = b;
}

