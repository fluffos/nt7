// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;35m靓[31m爆[1;33m你[1;34m双眼[2;37;0m[2;37;0m[2;37;0m", ({"allure"}));        
        set("gender", "女性");                
        set("long", "靓爆你双眼！[2;37;0m
它是小妞贼靓的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "alluring");
        set("owner_name", "小妞贼靓");
        set_temp("owner", "alluring");
        set_temp("owner_name", "小妞贼靓");
        ::setup();
}
