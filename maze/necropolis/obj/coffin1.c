#include <ansi.h>
inherit ITEM; 

int generate_taoist;
void set_generate_taoist(int i) {
        generate_taoist = i;
}
int query_generate_taoist() {
        return generate_taoist;
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
        object taoist;
        
        if(!arg || (arg!="coffin" &&  arg!="棺材")) 
                return notify_fail("你要推什么？\n");
                
        if(query_generate_taoist()) {
                message_vision("$N推开了棺材，但是里面什么都没有。\n",this_player());
                return 1;
        } else {
                message_vision("$N推开了棺材，里面滚出个人来。\n",this_player());
                taoist = new("/maze/necropolis/npc/taoist");
                taoist->move(environment(this_player()));
                set_generate_taoist(1);
                return 1;
        }
}