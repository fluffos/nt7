// copyright from Fengyun.

#include <ansi.h>
#include <command.h>

#define DOOM_PATH "/d/wuxi/xingzilin"
inherit F_DBASE;

string *additional_room = ({});
string *additional_npc = ({});

// 所有可能的方向
string *all_dir = ({
       "north","northeast","northwest","south",
       "southwest","southeast","east","west",
//       "northup","northdown","eastup","eastdown",
//       "westup","westdown","southup","southdown",
});

int    i, j, size, grid_size, flag, int_dir;
string *dyna_room, *room_names, *dirs, *rev_dirs, *cur_exits;
string dir1, dir2, dir3, dir4;
string rev_dir1, rev_dir2, rev_dir3, rev_dir4;
object dyna_npc, *room_object, *old_npc, cur_room;
mixed  *room_list, *npc_list, *temp_list;

int regenerate_map();

int clean_up() { return 1; }
void create()
{
       seteuid(ROOT_UID);
       set("channel_id", "系统精灵");
       CHANNEL_D->do_channel( this_object(), "sys", "杏子林地图已经启动。\n");
       call_out("regenerate_map",1);
}

int regenerate_map()
{
        int kk;

        remove_call_out("regenerate_map");
        CHANNEL_D->do_channel(this_object(),"sys", "开始重新生成杏子林地图。\n");

        room_list = get_dir(DOOM_PATH+"/dynamic/*.c");
        for(kk=0;kk<sizeof(room_list);kk++)
                room_list[kk] = DOOM_PATH+"/dynamic/"+room_list[kk];
        room_list += additional_room;

        dyna_room = ({});
        while(sizeof(room_list))
        {
                j = random(sizeof(room_list));
                dyna_room += ({room_list[j]});
                room_list -= ({room_list[j]});
        } // 随机分配位置完毕

        size = sizeof(dyna_room);


        room_object = ({});
        for(i=0;i<size;i++)
        {
                if( !(cur_room = find_object(dyna_room[i])) )
                        cur_room = load_object(dyna_room[i]);
                        delete("exits", cur_room);
                        delete("blocks", cur_room);
                        set("no_clean_up", 1, cur_room);
                        room_object += ({cur_room});
        }

        // 开始生成路径
        for(i=0;i<size;i++)
        {
                //生成四个不同的方向对
                dirs =  ({      "north","northeast","northwest","south",
                                "southwest","southeast","east","west",
                                //"northup","northdown","eastup","eastdown",
                                //"westup","westdown","southup","southdown",
                        });

                rev_dirs = ({   "south","southwest","southeast","north",
                                "northeast","northwest","west","east",
                                //"southdown","southup","westdown","westup",
                                //"eastdown","eastup","northdown","northup",
                           });

                int_dir = random(sizeof(dirs));
                dir1 = dirs[int_dir];
                rev_dir1 = rev_dirs[int_dir];
                dirs -= ({dir1});
                rev_dirs -= ({rev_dir1});

                int_dir = random(sizeof(dirs));
                dir2 = dirs[int_dir];
                rev_dir2 = rev_dirs[int_dir];
                dirs -= ({dir2});
                rev_dirs -= ({rev_dir2});

                if(i>0)
                {
                        set("exits/"+dir1, dyna_room[i-1], (room_object[i]));
                        set("exits/"+rev_dir1, dyna_room[i], (room_object[i-1]));
                }

                int_dir = random(size);

                if( (int_dir != i) && !(query("exits/"+rev_dir2, (room_object[int_dir]))) )
                {
                        set("exits/"+dir2, dyna_room[int_dir], (room_object[i]));
                        set("exits/"+rev_dir2, dyna_room[i], (room_object[int_dir]));
                }
                int_dir = random(size);
                tell_room(room_object[i],HIW"一阵天旋地转之后，你发现一切都已经变了...\n"NOR);
        }
        set("exits/south", DOOM_PATH+"/road4", (room_object[size-1]));
        set("exits/south", DOOM_PATH+"/road4", (room_object[0]));
        return 1;
}

