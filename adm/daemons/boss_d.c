// This program is a part of NT MudLIB
// Written by Lonely@nitan.org
// boss_d.c

#include <ansi.h>
#include <command.h> 

#define MAZE_DOOR       "/clone/misc/maze_door1"

mapping data;

void create()
{
        string file,key,value;
        string *lines;
        int i,sz;
        
        data=([]);
        file = replace_string(read_file("/adm/etc/boss_list"), "\r", "");  
        lines = filter_array(explode(file, "\n") - ({ "" }), (: $1[0] != '#' :)); 
        sz = sizeof(lines); 
        for( i=0;i<sz;i++ ) { 
                //while( strlen(lines[i]) && lines[i][0] == ' ' ) lines[i] = lines[i][1..<1]; 
                if( !stringp(lines[i]) || lines[i]=="" || sscanf(lines[i],"%s:%s",key,value)!=2 )
                        continue;
                data[key]=value;
        }
}

varargs void place_boss(string name, mixed flag)
{
        string file,where;
        object ob,room,door;
        
        //DEBUG_CHANNEL(sprintf("%s %O\n", name, flag));
        if( undefinedp(data[name]) ) return;
        where = data[name];
        room = get_object(where);
        if( !objectp(room) ) {
                return;
        }
        if( flag ) {
                file = "/maze/"+name+"/npc/dragon.c";
                if( file_size(file) < 0 ) return;
                ob = load_object(file);
                if( !objectp(ob) ) return;
                
                door = new(MAZE_DOOR); 
                set("maze_entry", "/maze/"+name+"/maze/entry", door); 
                door->move(room);
                SCHEDULE_D->set_event(1800, 0, this_object(), "remove_maze", ob->short(), room, door);
        } else {    
                if( sscanf(name, "%*s.data") ) {
                        file = "/adm/etc/boss/"+name;
                        if( file_size(file) < 0 ) return;
                        ob = "/adm/daemons/npc_d.c"->load_npc_data(file);
                } else {
                        file = "/kungfu/class/misc/"+name+".c";
                        if( file_size(file) < 0 ) return;
                        ob = new(file);
                } 
                if( !objectp(ob) ) return;

                ob->move(room);
                SCHEDULE_D->set_event(1800, 0, this_object(), "remove_boss", ob, room);
        }
        
        CHANNEL_D->channel_broadcast("news", HIG "有人发现" HIR + ob->short() + HIG "出现在" + 
                HIW + room->short() + HIY "(" + LOOK_CMD->locate(base_name(room)) + ")" HIG "一带活动。\n" NOR);  
}

void remove_maze(string name, object room, object door)
{
        if ( !room || !door ) return;
        
        tell_room(room, door->name()+"慢慢的消失了。\n", ({ door }));
        
        destruct(door);

        CHANNEL_D->channel_broadcast("news", HIG "听说" + HIW + 
                room->short() + "(" + LOOK_CMD->locate(base_name(room)) + ")" HIG "一带出现的" +
                HIR + name + HIG "消失了。\n" NOR);
}

void remove_boss(object ob, object room)
{
        if( !ob || !room ) return;
 
        tell_room(room, ob->name()+"急急忙忙的走了。\n", ({ ob }));

        CHANNEL_D->channel_broadcast("news", HIG "听说" + HIW +
                room->short() + "(" + LOOK_CMD->locate(base_name(room)) + ")" HIG "一带出现的" +
                HIR + ob->short() + HIG "消失了。\n" NOR);

        destruct(ob);
}
