// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("朱雀[2;37;0m[2;37;0m", ({"zhuque"}));        
        set("gender", "女性");                
        set("long", "五神兽之--朱雀。[2;37;0m
它是汤姆猫的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "tomcat");
        set("owner_name", "汤姆猫");
        set_temp("owner", "tomcat");
        set_temp("owner_name", "汤姆猫");
        ::setup();
}
