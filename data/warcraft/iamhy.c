// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m青龙[2;37;0m[2;37;0m", ({"qil"}));        
        set("gender", "男性");                
        set("long", "一只小青龙[2;37;0m
它是轩辕三光的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "iamhy");
        set("owner_name", "轩辕三光");
        set_temp("owner", "iamhy");
        set_temp("owner_name", "轩辕三光");
        ::setup();
}
