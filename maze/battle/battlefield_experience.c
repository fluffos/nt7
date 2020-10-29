#include <ansi.h>
#include <buff.h>
#include <daemon.h>
#include <feature.h>

inherit CONDITION_MOD;

string id               = "battlefield-experience";
string name     = HIC"无止尽的"NOR CYN"战争历练"NOR;
string type     = CONDITION_TYPE_POSITIVE;
int time                = 300;
int heartbeat   = 0;

int get_attr_value(int value)
{
        int buff;

        if( value < 100 )
                buff = 30;
        else if( value < 200 )
                buff = 20;

        else if( value < 300 )
                buff = 15;
        else if( value < 400 )
                buff = 10;
        else if( value < 500 )
                buff = 8;
        else
                buff = 6;

        return buff;

}

int get_abi_value(int value)
{
        int buff;

        if( value < 1000 )
                buff = 500;
        else if( value < 2000 )
                buff = 250;
        else if( value < 4000 )
                buff = 150;
        else if( value < 6000 )
                buff = 100;
        else if( value < 8000 )
                buff = 80;
        else
                buff = 60;

        return buff;
}


// 启动状态时的效果

void start_effect(object ob)
{
        addn(query_key()+"/"+BUFF_STR, get_attr_value(ob->query_str()), ob);
        addn(query_key()+"/"+BUFF_PHY, get_attr_value(ob->query_phy()), ob);
        addn(query_key()+"/"+BUFF_AGI, get_attr_value(ob->query_agi()), ob);
        addn(query_key()+"/"+BUFF_STAMINA_MAX, get_abi_value(ob->query_stamina_max()), ob);
        addn(query_key()+"/"+BUFF_HEALTH_MAX, get_abi_value(ob->query_health_max()), ob);
        addn(query_key()+"/"+BUFF_ENERGY_MAX, get_abi_value(ob->query_energy_max()), ob);

        ::start_effect(ob);
}

// 结束状态时的效果
void stop_effect(object ob)
{
        ::stop_effect(ob);
}

// 状态进行中的效果
void heart_beat_effect(object ob)
{


}

int stackable()
{
        return 300;
}
