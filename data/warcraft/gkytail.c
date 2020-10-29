// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("别看我对眼[2;37;0m[2;37;0m", ({"biudi"}));        
        set("gender", "男性");                
        set("long", "我发起火来连自己都打[2;37;0m
它是宝庆金楼的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "gkytail");
        set("owner_name", "宝庆金楼");
        set_temp("owner", "gkytail");
        set_temp("owner_name", "宝庆金楼");
        ::setup();
}
