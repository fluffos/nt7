// This program is a part of NITAN MudLIB 
// redl 2013/6
#include <ansi.h>

#define INIT_POND 10000000              //gold
#define DATA_FILE "/u/redl/obj/cigarette.o"
int pond = INIT_POND;

int do_save(int i)
{
        if (i < INIT_POND) i = INIT_POND;
        write_file(DATA_FILE, to_string(i), 1);
        return 1;
}

int do_load()
{
        int i;
        string s;
        if (file_size(DATA_FILE)>0) {
                s = read_file(DATA_FILE);
                i = to_int(s);
        }
        else i = INIT_POND;
        //write(NOR + "i:" + to_string(i) + "\n"+ NOR); 
        return i;
}

int chk_pond(object me)
{
        int i, rnd, flag = 0;
        pond = do_load();
        //write(HIG + "start:" + to_string(pond) + "\n"+ NOR); 

        for(i = 12; i > 0; i--) {       
                rnd = random(2);
                //write(NOR + "test:" + to_string(rnd) + "\n"+ NOR); 
                if (rnd) {
                        flag += 1;
                } else
                        break;
        }
        //write(HIG + "flag:" + to_string(flag) + "\n"+ NOR); 

        if (flag >= 12) {//连中12个1
                pond /= 2;
                //write(HIY + "win:" + to_string(pond) + "\n"+ NOR); 
                addn("balance", pond * 10000, me);
                addn("cigarette_gold", pond, me); //个人累计获奖的黄金
                log_file("static/cigarette", sprintf("(%s)%s(%s)获得头奖 %s 万两黄金。\n",  ctime(time()), me->name(), query("id", me), to_string(pond/10000))); 
                write(HIG + "小常子拱手涎脸道：恭喜恭喜，获得奖池里" + chinese_number(pond) + "两黄金，打赏一点？\n" + NOR);
                CHANNEL_D->channel_broadcast("rumor", "听说" + query("name", me) + "抽烟中了头奖，赢得了" + chinese_number(pond) + "两的奖池黄金。\n" + NOR);
                CHANNEL_D->channel_broadcast("rumor", "某人(Someone.)：你已经赢过" + chinese_number(query("cigarette_gold", me)) + "两了吧，这是想要逆天吗？\n" + NOR);
                do_save(pond);
                //write(HIY + "pond:" + to_string(pond) + "\n"+ NOR); 
                return 1;
        }

        if (flag >= 8) {
                //pond /= 50;
                //write(HIY + "win:" + to_string(pond) + "\n"+ NOR); 
                //addn("balance", pond * 10000, me);
                addn("balance", 10000000000, me);//改为每次100万，不从奖池里扣除
                //addn("cigarette_gold", pond, me); //个人累计获奖的黄金
                addn("cigarette_gold", 1000000, me); //个人累计获奖的黄金
                //log_file("static/cigarette", sprintf("(%s)%s(%s)获得大奖 %s 万两黄金。\n",  ctime(time()), me->name(), query("id", me), to_string(pond/10000))); 
                log_file("static/cigarette", sprintf("(%s)%s(%s)获得大奖 %s 万两黄金。\n",  ctime(time()), me->name(), query("id", me), to_string(1000000))); 
                //write(HIG + "小常子拱手涎脸道：恭喜恭喜，获得奖池里" + chinese_number(pond) + "两黄金，打赏一点？\n" + NOR);
                write(HIG + "小常子拱手涎脸道：恭喜恭喜，获得奖池里" + chinese_number(1000000) + "两黄金，打赏一点？\n" + NOR);
                //CHANNEL_D->channel_broadcast("rumor", "听说" + query("name", me) + "抽烟中了大奖，赢得了" + chinese_number(pond) + "两的奖池黄金。\n" + NOR);
                //CHANNEL_D->channel_broadcast("rumor", "某人(Someone.)：你已经赢过" + chinese_number(query("cigarette_gold", me)) + "两了吧，这是狗屎运气吗？\n" + NOR);
                CHANNEL_D->channel_broadcast("rumor", "听说" + query("name", me) + "抽烟中了大奖，赢得了" + chinese_number(1000000) + "两黄金。\n" + NOR);
                CHANNEL_D->channel_broadcast("rumor", "某人(Someone.)：你已经赢过" + chinese_number(query("cigarette_gold", me)) + "两了吧，这是狗屎运气吗？\n" + NOR);
                //pond *= 49;
                //do_save(pond);
                //write(HIY + "pond:" + to_string(pond) + "\n"+ NOR); 
                return 1;
        }

        pond += 10000;  //累积50%香烟售价
        do_save(pond);
        //write(RED + "pond:" + to_string(pond) + "\n"+ NOR); 
        return 1;
}

int ask_pond(string name)
{
        object me = this_player();
        pond = do_load();
        tell_object(me, CYN + name + "鬼鬼祟祟地告诉你：听说奖池里有" + chinese_number(pond) + "两黄金，抽烟中奖可拿走部分。\n" + NOR); 
        return 1;
}



