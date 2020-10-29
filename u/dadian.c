#include <ansi.h>
#include <room.h>

inherit PRIVATE_ROOM;

int clean_up() { return 1;} 

void create()
{
              set("short", "化乐天大殿"); 
              set ("long", 
          "这里是男主人红莲老祖和女主人芝芝品茶和接待朋友的地方("CYN"sit"NOR")。\n"
      "侧面是两扇屏风，正中有些桌椅，上方悬挂一匾上书：\n" 
          "    " BBLU CYN "╔───────╤───────╗\n" NOR
          "    " BBLU CYN "┃" NOR BBLU HIC "把盏衔杯意气深，兄兄弟弟抑何亲" NOR BBLU CYN "┃\n" NOR
          "    " BBLU CYN "┃" NOR BBLU HIC "一朝平地风波起，此际相交才见心" NOR BBLU CYN "┃\n" NOR
          "    " BBLU CYN "╚───────╧───────╝\n" NOR


        ); 


        set("exits", ([
                   //"west"   : "/u/gigi/startroom",
                "north"  : "/u/redl/houdian",
                "south"  : __DIR__"dating",
        ]));

        set("objects", ([ 
                                "/u/redl/npc/queen" : 1, 
                                "/u/redl/obj/table" : 1,  
        ])); 

                set("no_fight", 1); 
                set("no_rideto", 1);
                set("no_flyto", 1);
        set("no_sleep_room", 1);

        setup();

        set("room_owner", "红莲老祖");
        set("room_name", "莲池");
        set("room_id", "redl");
        set("room_owner_id", "redl");
        set("room_position", "溪岸小路");
}


void init()
{
        add_action("do_sit", "sit");
        delete_temp("has_sit", this_player());
}

int do_sit(string arg)
{
        object me;
        string sex;
        int tea = 50000;

        me = this_player();
        
        if (!query_temp("can_enterredlroom", me) && query("id", me) != "redl" && query("couple/couple_id", me) != "redl") return notify_fail("傀儡将军对着你嘿嘿嘿奸笑了几声。\n");
        
        if ( me->is_busy() ) {
                        tell_object(me, "你还是忙完手头上的事情再说吧。\n");
                        return 1;
                }
        me->start_busy(2);
        
        sex = query("gender", me);
        
        if( query_temp("has_sit", me) )
        {
                switch(random(7)) {
                        case 0:
                        case 1:
                        message_vision(CYN "$N默默地若有所思，前后摇了摇椅子。\n" NOR, me);
                        break;
                case 2:
                        case 3:
                        message_vision(CYN "$N轻轻伸手捂住嘴，小声地咳嗽了几声。\n" NOR, me);
                        break;
                case 4:
                        case 5:
                        message_vision(CYN + ((sex=="男性")? "$N不知道想起了什么事，裂开厚嘴唇呵呵笑了笑。\n" : "$N不知道想起了什么事，眯着眼睛笑得像月牙儿。\n") + NOR, me);
                        break;
                default:
                        message_vision(CYN "$N端起桌上的灵芝莲子茶，慢慢地送到唇边抿了一口。\n" NOR, me);
                                        if ( !query_temp("has_drinkredltea", me) ) {
                                                call_other(GIFT_D, "bonus", me, ([ "exp":tea, "pot":tea/4, "mar":tea/10, "prompt":"你在喝下灵芝莲子茶后"]));
                                message_vision(HIG "$N意犹未尽，“啧啧”地咂了几下嘴巴。\n" NOR, me);
                                        }
                                        set_temp("has_drinkredltea", 1, me);//不quit后第二次再获邀请来这里，是不能再有效果的了
                        break;
            }
            return 1;
        }

                                message_vision(CYN "$N寻了一把空椅子，轻轻坐了下来。\n" NOR, me);
                                set_temp("has_sit", 1, me);
        return 1;
}

int valid_leave(object me, string dir)
{
                string sex = query("gender", me);
                
        if( query_temp("has_sit", me) )
        {
                        message_vision(CYN + ((sex=="男性")? "$N整了整衣衫，离开椅子站了起来。\n" : "$N抖了抖裙子，离开椅子站了起来。\n") + NOR, me);
                        delete_temp("has_sit", me);
        }

        return ::valid_leave(me, dir);
}


