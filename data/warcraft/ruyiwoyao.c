// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;35m粉木耳[2;37;0m[2;37;0m", ({"baihu"}));        
        set("gender", "女性");                
        set("long", "  [2;37;0m
它是杜子腾的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "ruyiwoyao");
        set("owner_name", "杜子腾");
        set_temp("owner", "ruyiwoyao");
        set_temp("owner_name", "杜子腾");
        ::setup();
}
