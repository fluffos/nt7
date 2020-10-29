// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37;41m七剑[2;37;0m[2;37;0m", ({"zuesgs"}));        
        set("gender", "男性");                
        set("long", "哈哈[2;37;0m
它是叶七的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "zuesg");
        set("owner_name", "叶七");
        set_temp("owner", "zuesg");
        set_temp("owner_name", "叶七");
        ::setup();
}
