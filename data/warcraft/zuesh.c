// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37;41m八[1;34m卦[2;37;0m[2;37;0m", ({"zueshs"}));        
        set("gender", "男性");                
        set("long", "哈哈[2;37;0m
它是叶八的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "zuesh");
        set("owner_name", "叶八");
        set_temp("owner", "zuesh");
        set_temp("owner_name", "叶八");
        ::setup();
}
