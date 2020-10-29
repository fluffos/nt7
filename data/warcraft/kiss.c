// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("舌灿莲花[2;37;0m[2;37;0m", ({"lick"}));        
        set("gender", "女性");                
        set("long", "舔一下...[2;37;0m
它是小嘴冰凉的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "kiss");
        set("owner_name", "小嘴冰凉");
        set_temp("owner", "kiss");
        set_temp("owner_name", "小嘴冰凉");
        ::setup();
}
