// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m大白虎[2;37;0m[2;37;0m", ({"wtiger"}));        
        set("gender", "女性");                
        set("long", "这是长隆野生动物园的变异大白虎[2;37;0m
它是毒小宝的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "kimid");
        set("owner_name", "毒小宝");
        set_temp("owner", "kimid");
        set_temp("owner_name", "毒小宝");
        ::setup();
}
