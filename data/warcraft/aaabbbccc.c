// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("白虎[2;37;0m[2;37;0m", ({"baihu"}));        
        set("gender", "男性");                
        set("long", "虎中之王[2;37;0m
它是芳华的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "aaabbbccc");
        set("owner_name", "芳华");
        set_temp("owner", "aaabbbccc");
        set_temp("owner_name", "芳华");
        ::setup();
}
