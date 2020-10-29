// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("摩托车[2;37;0m[2;37;0m", ({"rune"}));        
        set("gender", "女性");                
        set("long", "125[2;37;0m
它是路人甲的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "qoo");
        set("owner_name", "路人甲");
        set_temp("owner", "qoo");
        set_temp("owner_name", "路人甲");
        ::setup();
}
