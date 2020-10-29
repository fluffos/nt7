// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m叫花鸡[2;37;0m[2;37;0m", ({"wok"}));        
        set("gender", "女性");                
        set("long", "叫花鸡!!![2;37;0m
它是夜尔尔的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "wokk");
        set("owner_name", "夜尔尔");
        set_temp("owner", "wokk");
        set_temp("owner_name", "夜尔尔");
        ::setup();
}
