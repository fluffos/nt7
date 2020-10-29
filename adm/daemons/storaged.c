// leagued.c
/*
每个人一个mapping
每个人一个计数器，计算他曾经存放过多少个物品
存放物品都会有一个序列号
根据此序列号取出物品
原生物件不能存放
按月租用
租用代价要易于修改

*/
#include <ansi.h>

// #pragma optimize
// #pragma save_binary

inherit F_SAVE;
inherit F_DBASE;

void create()
{
        mapping m;
        seteuid(getuid());
        restore();
        m=query_entire_dbase();
        if(!mapp(m)||undefinedp(m["data"]))
        {
                set("data",([]));
                save();
        }
}

void remove()
{
        save();
}

public void mud_shutdown()
{
        save();
}

public string query_save_file() { return DATA_DIR "storage"; }

//=================具体实现部分=======================

int DoMonFee(object me,int mon)
{
        mixed res;
        int onl,fee,j;
        string arg,sql;
        arg=query("id", me);
        res=DATABASE_D->do_sql("select on_time,fee_time from users where id="+DB_STR(arg));
        if(!res)
        {
                write("查询出错，请询问游戏管理员。\n");
                return 0;
        }
        else
        {
                sscanf(res[0]+"0","%d",onl);
                sscanf(res[1]+"0","%d",fee);
                onl/=10;fee/=10;

                if(wizardp(this_player())) write("你目前的游戏点可用数"+(fee-onl/3600)+"\n");

                if(fee - onl/3600 > (mon*150)+50  )
                {
                        sql="update users set fee_time=fee_time-"+150*mon+",endrgt=now() where id="+DB_STR(arg);
                        if ((DATABASE_D->do_query(sql))<1)
                        {
                                write("扣除点数失败，请尽快联系游戏管理员查明原因。\n");
                                return 0;
                        }
                        else
                        {
                                //扣除点数成功
                                me->save();
                                //重新从数据库取，以验证是否真的已经改变
                                       res=DATABASE_D->do_sql("select fee_time from users where id="+DB_STR(arg));
                                       sscanf(res[0]+"0","%d",j);
                                sql=sprintf("insert into reg_log (id,add_hours,new_fee_time,time) values (%s,%d,%d,now())",DB_STR(arg),-150*mon,j/10);
                                if(DATABASE_D->do_query(sql) < 1)
                                        log_file("mysql.log",ctime(time())+":"+sql);
                                write("你的游戏点已经扣除了"+mon*150+"点！\n");
                        }
                }
                else
                {
                        write("你的游戏点已经不够用于开通（或续费）储物柜了（你得有至少"+(mon*150+50)+"点才可以），请赶快汇款购卡吧。\n");
                        return 0;
                }
        }
        return 1;
}

int ExpireDate(string id)
{
        return query("data/"+id+"/expiredate");
}

int AccountOk(string id)
{
        return (ExpireDate(id)>=time());
}

int ExistAccount(string id)
{
        mapping m=query_entire_dbase();
        if(undefinedp(m["data"]))
        {
                set("data",([]));
                return 0;
        }
        return !undefinedp(m["data"][id]);
}

int CancelAccount(object me)
{
        mapping m;
        m=query("data/"+query("id", me));
        if(!mapp(m))
        {
                write("你还没有开过户呀！\n");
        }
        else
        {
                if( query_temp("sure_cancel", me) != 1 )
                {
                    write("帐户取消我们也不会退回租费的哟！\n如果你还没想好，可以先把东西都取走。\n(请注意，再次输入取消命令将不再提示本信息)\n");
                    set_temp("sure_cancel", 1, me);
                    return 1;
                }
                m=query("data/"+query("id", me)+"/objects");
                if(sizeof(m)==0)
                {
                        m=query("data/"+query("id", me));
                        if(!mapp(m))
                        {
                            write("你的帐户未能成功取消，请联系管理员。\n");
                            return 1;
                        }
                        log_file("storage.log","cancel:"+query("name", me)+"("+query("id", me)+")取消了帐户！类型："+m["typ"]+"\n");
                        delete("data/"+query("id", me));
                        write("你的帐户已经成功取消！\n");
                }
                else
                {
                        write("取消帐户前，请先将你的物品全部取出来！\n");
                }
        }
        return 1;
}

int OpenAccount(object me,string arg)
{
        mapping m;
        string id;
        int i,j,k,obcount;
        id=query("id", me);
        if(ExistAccount(id))
        {
            write("你已经开过户了！请使用cw fee <几个月> 续租！\n");
            return 1;
        }
        if(sscanf(arg,"%d",i)!=1)
            i=0;
        if( query_temp("yes_i_know", me) != 1 )
        {
            set_temp("yes_i_know", 1, me);
            write("储物柜每月租费为：\n类型0\t需要100两黄金\n类型1\t需要200两黄金\n类型2\t需要花150个游戏点\n"
                "请确认你已经知道以上资费情况，再次输入开户命令将不再提示直接开户！\n");
            return 1;
        }
        switch(i)
        {
                case 0:
                        k=me->pay_money(1000000);
                        obcount=35;
                        break;
                case 1:
                        k=me->pay_money(2000000);
                        obcount=80;
                        break;
                case 2:
                        //具体的扣点
                        if(k=DoMonFee(me,1))
                                obcount=500;
                        break;
                default:
                        k=0;
                        obcount=0;
        }
        if(k)
        {
                j=time()+86400*30;
                //初始化一些参数
                m=([
                        "cnt":0,
                        "typ":i,
                        "expiredate":j,
                        "max_obs":obcount,
                        ]);
                set("data/"+query("id", me),m);
                log_file("storage.log","open:"+query("name", me)+"("+query("id", me)+")开设了第"+i+"类帐户！\n");
                write("恭喜你，你的开户已经成功。你的储物柜可以储藏"+obcount+"件物品，你可以用到"+CHINESE_D->cctime(j)+"为止。\n");
                save();
                return 1;
        }
        else
        {
                if(i!=2)
                        write("对不起，你的钱未带够！请带上足够的钱然后使用cw open 0 或cw open 1来开户！\n"+i+" "+k);
                else
                        write("对不起，你的游戏点不够，请先续上足够的游戏点然后使用cw open 2来开户！\n");
        }
        return 1;
}

void ListObject(object me)
{
        string k,res="你的储物柜里有：\n";
        mapping m,om;
        int i,j;
        string id;
        id=query("id", me);
        if(!ExistAccount(id))
        {
                write("请先开户！\n");
                return ;
        }
        if(!AccountOk(id))
        {
                write("请先续费！\n");
                return ;
        }
        i=wizardp(me);
        m=query("data/"+id+"/objects");
        if(!mapp(m)||sizeof(m)<1)
        {
                write("你还没有储存过什么物品。\n");
                return ;
        }
        j=0;
        foreach(k in keys(m))
        {
                om=m[k];
                j++;
                res+=sprintf("第%d个物品 编号%5s ： %20s(%10s) 数量：%d %s\n",j,k,om["name"],om["id"],om["num"],(i?om["file"]:""));
        }
        me->start_more(res);
}

void PutObject(object me,string arg)
{
        object ob;
        string file,id,key,str;
        mapping m;
        int i,j;
        id=query("id", me);
        if(!ExistAccount(id))
        {
                write("请先开户！\n");
                return ;
        }
        if(!AccountOk(id))
        {
                write("请先续费！\n");
                return ;
        }
         ob=present(arg,me);
        if(!objectp(ob))
        {
                write("没有发现物品"+arg+"！\n");
                return ;
        }
        file=file_name(ob);
        //什么样的物品不能存呢？
        if(strsrch(file,"#")==-1 || ob->is_character() || living(ob))
        {
                write("对不起，该物品不可以储存！\n");
                return ;
        }
        if( query("task_ob", ob) || query("unique", ob) ||
            query("no_store", ob) || query("maze_item", ob) ||
            query("bindable", ob) || query("set_data", ob) )
        {
                write("对不起，该物品不可以储存！\n");
                return ;
        }
        if( query("money_id", ob) )
        {
                write("对不起，金钱不可以被储存！\n");
                return ;
        }
        //如何判定食物呢？
        if(mapp(m=ob->query_entire_dbase()))
        {
                if(!undefinedp(m["food_remaining"])||!undefinedp(m["food_supply"]))
                {
                        write("对不起，食物不可以储存！\n");
                        return ;
                }
        }

        key="data/"+id+"/";
        if(sizeof(query(key+"objects"))>=query(key+"max_obs"))
        {
            write("对不起。你已经存储了"+query(key+"cnt")+"件物品了。不能再存储更多的东西了。\n");
            return ;
        }

        str=query("unit", ob);
        if(!str) str="个";
        j=ob->query_amount();
        if(j<1) j=1;
        m=([
                "file":file,
                "name":query("name", ob),
                "id":query("id", ob),
                "unit":str,
                "num":j,
                ]);
        i=query(key+"cnt");
        i++;
        set(key+"cnt",i);
        set(key+"objects/"+i,m);
        destruct(ob);
        if(objectp(ob))
        {
                write("错误！储存失败，请联系管理员。\n");
                set(key+"cnt",i-1);
                delete(key+"objects/"+i);
        }
        else
                write(m["name"]+"已经储存好了！编号："+i+" 。\n");
        //也许应该用心跳来控制
        save();
        return ;
}

void GetObject(object me,string arg)
{
        string kid,*ks,id;
        string res="";
        object ob;
        mapping m;
        int i,ok=0;
        id=query("id", me);
        if(!ExistAccount(id))
        {
                write("请先开户！\n");
                return ;
        }
        if(!AccountOk(id))
        {
                write("请先续费！\n");
                return ;
        }
         if(!arg||arg=="")
        {
                write("你要取走什么物品？\n");
                return ;
        }
        arg=lower_case(arg);
        kid="data/"+id+"/objects";
        m=query(kid);
        if(sizeof(m)<1)
        {
                write("你什么物品都没有储存着，还想拿走什么？\n");
                return ;
        }
        ks=keys(m);
        for(i=0;i<sizeof(ks);i++)
        {
                if(ks[i]==arg || m[ks[i]]["id"]==arg)
                {
                        m=m[ks[i]];
                        ok=1;
                        break;
                }
        }
        if(ok)
        {
                res=m["file"];
                sscanf(res,"%s#%*s",res);
                ob=new(res);
                if(objectp(ob))
                {
                        ob->set_amount(m["num"]);
                        if(ob->move(me))
                        {
                                write("你从储物柜取出了"+m["name"]+"("+m["id"]+") 。\n");
                                //write("你从储物柜取出了"+ob->query("name")+"("+ob->query("id")+")。\n");
                                delete(kid+"/"+ks[i]);
                                //也许应该用心跳来控制
                                save();
                                return;
                        }
                        else
                        {
                                write("你身上已有物品负荷过重，无法取出该物品。\n");
                                return;
                        }
                }
        }
        write("取出物品，请输入cw get <物品编号>，编号可用cw list指令查看。\n");
        return ;
}

int DoFee(object me,string arg)
{
    int mon,k,i;
    string id=query("id", me);
    mon=1;
    if(!ExistAccount(id))
    {
            write("请先开户！\n");
            return 1;
    }
    if(AccountOk(id))
    {
            write("你还没必要续费！你的到期时间是"+CHINESE_D->cctime(query("data/"+id+"/expiredate"))+"\n");
            return 1;
    }
    if(arg)
        sscanf(arg,"%d",mon);
    if(mon<1) mon=1;
    if(mon>3)
    {
        write("对不起，一次最多续三个月！\n");
        return 1;
    }
    switch(i=query("data/"+id+"/typ"))
    {
            case 0:
                    k=me->pay_money(1000000*mon);
                    break;
            case 1:
                    k=me->pay_money(2000000*mon);
                    break;
            case 2:
                    //具体的扣点
                    k=DoMonFee(me,mon);
                    break;
            default:
                    k=0;
    }
    if(k)
    {
            int expiredate=query("data/"+id+"/expiredate");
            expiredate+=86400*30*mon;
            set("data/"+id+"/expiredate",expiredate);
            log_file("storage.log","open:"+query("name", me)+"("+query("id", me)+")为第"+i+"类帐户续了"+mon+"个月！\n");
            write("恭喜你，你的续费已经成功。你可以用到"+CHINESE_D->cctime(expiredate)+"为止。\n");
            save();
            return 1;
    }
    else
    {
            if(i!=2)
                    write("对不起，你的钱未带够！请带上足够的钱然后使用cw fee <几个月> 命令来续费！\n"+i+" "+k);
            else
                    write("对不起，你的游戏点不够，请先续上足够的游戏点然后使用cw fee <几个月> 来续费！\n");
    }
    return 1;
}

int ShowHelp(object me)
{
        string helpstr=
        "help              获取本帮助信息\n"
        "fee <租期>        为储物柜续费，如果欠费则会先补欠费。租期为月数。\n"
        "open <0-2>        开设储物柜帐户，在该命令后的参数0-2分别代表三种不同的租用方式\n"
        "cancel            取消自己的储物柜帐户。你必须先将里面的物品全部取出来后才可取消\n"
        "list              列出自己的储物柜里都有些什么物品\n"
        "put <物品ID>      将身上的某个物品放到储物柜里（不是什么都可以存放的）\n"
        "get <编号|物品ID> 将储物柜里某个编号的物品取出来\n"
        ;
        write(helpstr);
        MYGIFT_D->check_mygift(this_player(1), "newbie_mygift/cangku");
        return 1;
}
