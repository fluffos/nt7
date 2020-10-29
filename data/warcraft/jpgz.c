// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m血灵[2;37;0m[2;37;0m", ({"xueling"}));        
        set("gender", "女性");                
        set("long", "四大神兽之朱雀一族，后为极品公子所驯服。[2;37;0m
它是极品公子的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "jpgz");
        set("owner_name", "极品公子");
        set_temp("owner", "jpgz");
        set_temp("owner_name", "极品公子");
        ::setup();
}
