// Code of JHSH
// snake_room.h 蛇谷中有蛇的房间

void check_snake(object, string);
void smoke_snake(object, object, string);
#include <ansi.h>

void init()
{
        object here = this_object();
        set("can_perform_shewu", 1, here);
        set("enter_shegu", 1, this_player());
        delete_temp("search", this_player());

        if( query("hide_snake", here)<1 && 
        (time()-query("last_search", here)>180 || !query("last_search", here)) )
                set("hide_snake", 1+random(3), here);

        add_action("do_search", "search");
        add_action("do_use","use");
        add_action("do_burn","burn");
}

string look_bush()
{
        string desc;
        if(!query("searched/bush")) desc = "一处低矮的灌木丛。\n";
        else desc = "一处低矮的灌木丛，地上有些断折掉落的枝叶。\n";        
        return desc;
}

string look_crack()
{
        string desc;
        if(!query("searched/crack")) desc = "树根间的裂缝，旁边生着丛丛乱草。\n";
        else desc = "树根间的裂缝，附近的杂草倒向两边，似乎被拨动过。\n";        
        return desc;
}

string look_cave()
{
        string desc;
        if(!query("searched/cave")) desc = "山壁下的一个小洞，洞口土地没什么砂土，颇为光滑。\n";
        else desc = "山壁下的一个小洞，洞口土地有些枝叶烧剩的灰烬。\n";        
        return desc;
}

int do_search(string arg)
{
        object me, here, weapon;
        string place;
        
        me = this_player();
        here = this_object();
        weapon=query_temp("weapon", me);

        if( me->is_busy() || query_temp("pending/exercising", me) )
                return notify_fail("你现在正忙着呢。\n");

        if( !objectp(weapon) || (query("skill_type", weapon) != "staff"
         && query("skill_type", weapon) != "club"
         && query("skill_type", weapon) != "stick") )
                return notify_fail("空手寻蛇太危险了，先拿点趁手的工具吧。\n");


        if(arg == "grass" && query("grass") ) {
                place = "草丛";
                message_vision("$N用"+weapon->name()+"拨动附近的草丛。\n", me);
                addn("jingli", -20, me);
                set("searched/grass", 1);
        }
        
        else if(arg == "bush" && query("bush") ) {
                place = "树丛";
                message_vision("$N挥着"+weapon->name()+"，打动四周的树丛枝叶，发出沙沙的轻响。\n", me);
                addn("jingli", -40, me);
                set("searched/bush", 1);
        }
        else if(arg == "crack" && query("crack") ) {
                place = "树根裂缝";
                message_vision("$N用"+weapon->name()+"在树根的裂缝处敲了敲。\n", me);
                addn("jingli", -10, me);
        }

        else if(arg == "cave" && query("cave") ) {
                place = "洞";
                message_vision("$N用"+weapon->name()+"在洞口地面托、托地轻敲着。\n", me);
                addn("jingli", -10, me);
        }
        else return notify_fail("你要搜索哪个地方？\n");

        addn_temp("search/"+place, 1, me);
        me->start_busy(1);

        if( query_temp("search/"+place, me)<3+random(3) )
                return 1;

        if(query("hide_snake") > 0) {
                check_snake(me, place);
        }
        else return notify_fail("找了这麽久，你觉得"+place+"中应该是不会藏着蛇了。\n");

        return 1;
}

void check_snake(object me, string place)
{
        object snake, here;
        int i;

        here = this_object();

        addn("hide_snake", -1, here);
        set("last_search", time(), here);

        if( place == "草丛" || place == "树丛" ) {
                if( place == "树丛" ) {
                        i = random(4) + 1;
                        set("searched/bush", 1);
                        }
                else {
                        i = random(4);
                        set("searched/grass", 1);
                        }
                snake = new("/d/baituo/npc/bt_snake");
                set("frightened", 1, snake);
                snake->set_kind(i);
                snake->move(here);
                message_vision(HIR"忽听"+place+"中簌簌响动，一条"+snake->name()+"窜了出来！\n"NOR, me);
                snake->kill_ob(me);
        }
        else message_vision(place+"中传出一阵细微的声响，似乎有什麽东西，但是没有出来。\n"NOR, me);

        delete_temp("search/"+place, me);

        return;
}

int do_use(string arg)
{
        object me = this_player();

        if( !arg || arg=="" ) return 0;
        if (!present("fire", me))  return 0;

        if( arg=="fire" ) 
        write("你将火折点燃。\n");
        return 1;
}

int do_burn(string arg)
{
        object me, branch;
        string place;
        me = this_player();

        if( !arg || arg=="" ) return 0;
        if (!present("fire", me))  return 0;

        if( me->is_busy() || query_temp("pending/exercising", me) )
                return notify_fail("你现在正忙着呢。\n");

        if( !objectp(branch = present(arg, me))  && !objectp(branch = present(arg, environment(me)))  )
                return notify_fail("你要烧什麽？\n");

        if( query("id", branch) != "shuzhi" )
                return notify_fail("如果你想熏蛇，找些树枝之类的东西来烧吧。\n");

        if( query("burning", branch) )
                return notify_fail("树枝已经点燃了。\n");

        if( query("crack") ) {
                place = "树根裂缝";
                if(!query("searched/crack")) message_vision("$N将树根前的杂草拨开。\n", me);
        }
        else if( query("cave") ) place = "洞";
        else return notify_fail("在这里烧树枝也没什麽用。\n");

        message_vision(HIR"$N将"+branch->name()+HIR"堆在"+place+"前，用火折点燃。\n"NOR, me);
        message_vision(WHT"一股浓烟慢慢涌入"+place+"里........\n\n"NOR, me);
        
        set("name", "点燃的"+branch->name(), branch);
        set("long",query("long",  branch)+"现在正燃烧着，冒出浓浓的烟雾。\n", branch);
        set("burning", 1, branch);
        set("no_get", 1, branch);
        branch->move(this_object());
        remove_call_out("smoke_snake");
        call_out("smoke_snake", 7+random(3), me, branch, place); 
        me->start_busy(2);

        return 1;
}


void smoke_snake(object me, object branch, string place)
{
        object snake, here;
        int i;

        here = this_object();

        if(query("hide_snake") < 1 ) {
                message_vision("烟熏了老半天，树枝都烧成灰了，"+place+"里却一点动静也没有。\n", me);
                destruct(branch);
                return;
        }

        addn("hide_snake", -1);
        set("last_search", time(), here);

        if( place == "树根裂缝" ) {
                i = random(5) + 3;
                set("searched/crack", 1);
        }
        else {
                i = random(3) + 5;
                set("searched/cave", 1);
        }

        snake = new("/d/baituo/npc/bt_snake");
        set("frightened", 1, snake);
        snake->set_kind(i);
        snake->move(here);
        message_vision(HIR"忽听一阵飕飕异声，一条$N忍不住烟熏，从"+place+"中窜了出来！\n"NOR, snake);
        if(environment(me) == this_object())
        snake->kill_ob(me);

        delete_temp("search/"+place, me);
        destruct(branch);

        return;
}
