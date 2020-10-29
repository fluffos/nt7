// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m淫娃[2;37;0m[2;37;0m", ({"yinwa"}));        
        set("gender", "女性");                
        set("long", "永远无法满足的欲望女孩[2;37;0m
它是段玉的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "warrierh");
        set("owner_name", "段玉");
        set_temp("owner", "warrierh");
        set_temp("owner_name", "段玉");
        ::setup();
}
