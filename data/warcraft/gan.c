// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m红脸老猪[2;37;0m[2;37;0m", ({"redi"}));        
        set("gender", "女性");                
        set("long", "。。。。[2;37;0m
它是干将的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "gan");
        set("owner_name", "干将");
        set_temp("owner", "gan");
        set_temp("owner_name", "干将");
        ::setup();
}
