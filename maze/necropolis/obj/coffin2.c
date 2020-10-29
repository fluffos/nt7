#include <ansi.h>
inherit ITEM; 

int generate_monk;
void set_generate_monk(int i) {
        generate_monk = i;
}
int query_generate_monk() {
        return generate_monk;
}

void create()
{
        set_name("棺材", ({"coffin"}) );
        set_weight(300);
        set("no_get", 1);
        set("unit", "轮");
        set("long", "一具腐朽的棺木,好像可以推开盖子(push)。\n");
        set("value", 2000);
        setup();
} 

void init () {
        add_action("do_push","push");
}

int do_push(string arg) {
        object monk;
        
        if(!arg || (arg!="coffin" &&  arg!="棺材")) 
                return notify_fail("你要推什么？\n");
                
        if(query_generate_monk()) {
                message_vision("$N推开了棺材，但是里面什么都没有。\n",this_player());
                return 1;
        } else {
                message_vision("$N推开了棺材，里面居然有个和尚。\n",this_player());
                monk = new("/maze/necropolis/npc/monk");
                monk->move(environment(this_player()));
                message_vision("$N叹了口气道：还是被找着了。\n",monk);
                set_generate_monk(1);
                return 1;
        }
}