#include <ansi.h> 

int help(object me);
int main(object me, string arg)
{
        object *virlist;
        object ob;
        object eob;
        string str;
        string target;
        int option = 0;
        int amount;
        int i;

        amount = query("flowers/amount", me);
        if( !arg || arg == "" )
        {
                write(HIW "你目前拥有 " + amount + " 张新手导师评价票。\n" NOR);
                if( sizeof(virlist = DB_D->query_data("virlist/teacher")) )
                {
                        str = HIC "\n≡"  + HIM "游戏中所有在职导师" + HIC + "≡\n" NOR;  
                        for (i = 0; i < sizeof(virlist);i ++) 
                        {
                                if( objectp(eob = find_player(virlist[i])) )
                                {
                                        str += HIY + eob->name() + HIY + "(" + virlist[i] + ")--在线--"; 
                                        str += HIY "鲜花 " + query("flowers/recognition", eob) + " 朵--"; 
                                        str += HIY "臭鸡蛋 " + query("flowers/antipathy", eob) + " 个\n" NOR; 
                                }
                                else
                                {
                                        eob = UPDATE_D->global_find_player(virlist[i]); 
                                        if( !objectp(eob) ) continue; 
                                        str += HIY + eob->name() + HIY + "(" + virlist[i] + ") --离线时间：" + NOR; 
                                        str += HIY + sprintf("%d", (time() - query("last_on", eob)) / 86400) + "天--";
                                        str += HIY "鲜花 " + query("flowers/recognition", eob) + " 朵--"; 
                                        str += HIY "臭鸡蛋 " + query("flowers/antipathy", eob) + " 个\n" NOR; 
                                        UPDATE_D->global_destruct_player(eob, 1); 
                                }
                        }
                        write(str);
                }
                return 1;
        }

        if( amount < 1 )
                return notify_fail(HIW "你目前拥有 0 张新手导师评价票。\n" NOR);

        if( sscanf(arg, "-a %s", target) )
                option = 1;
        else if( sscanf(arg, "-o %s", target) )
                option = 0;
        else
                return help(me);

        if( !objectp(ob = UPDATE_D->global_find_player(target)) ) 
                return notify_fail("没有这个人！\n"); 

        if( query("viremploy/job", ob) != "新手导师" && query("viremploy/job", ob) != "高手导师" )
        {
                UPDATE_D->global_destruct_player(ob, 1);
                write("他不是新手导师，你只能给新手导师投评价票。(who -v可查询新手导师)\n");
                return 1;
        }

        addn("flowers/amount", -1, me);
        if( option )
        {
                addn("flowers/recognition", 1, ob);
                CHANNEL_D->channel_broadcast("news", me->query_idname() + "对新手导师" + ob->query_idname()+"的工作表示认可，送上"
                        HIW"一朵"HIY"美丽"HIW"的"HIG"鲜"HIR"花"NOR"。\n");
        }
        else
        {
                addn("flowers/antipathy", 1, ob);
                CHANNEL_D->channel_broadcast("news", me->query_idname() + "对新手导师" + ob->query_idname()+"的工作极不满意，扔给"
                        HIW"一个"HIY"极臭"HIW"的"HIG"臭"HIR"鸡蛋"NOR+YEL"，砸的他满脸开花。\n");
        }

        UPDATE_D->global_destruct_player(ob, 1);  
        return 1; 

}

int help(object me)
{
        write("flowers                 查询自己拥有新手导师评价票数\n"
              "flowers -a <id>         投给新手导师一张满意的评价票\n"
              "flowers -o <id>         投给新手导师一张不满意的评价票\n");
        return 1;
}
