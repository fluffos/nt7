int errs( string msg )
{
    write( msg );
    return 1;
}

int me_ok(object me)
{
    object env;

    if( !me || me != query("my_master") )
        return 0;
    if( query_temp("huanjing", me) != "start"
       || query_temp("hj_hp", me)<1
       || !query_temp("hj_hp_max", me )
    )
        return 0;
    env = environment(me);
    if( !env || !query("room_mark", env) )
        return 0;
    return 1;
}

void hj_halt(string msg)
{
    object me = query("my_master");
    if( !me ) return;

    if( msg != "" )
    {
        if( strsrch( msg, "$n" ) == -1 )
            message_vision( msg, me);
        else message_vision( msg, me,
            query_temp("hj_healing", me)?
            query_temp("hj_healing", me):
            query_temp("hj_fighting", me));
    }

    delete_temp("hj_need_waiting", me);
    delete_temp("hj_healing", me);
    delete_temp("hj_fighting", me);
    delete("pfm_ready");
}

string get_deng_pic( int deng )
{
    string co1 = HIC, co2 = HIB, co3 = BLU;

    switch( deng )
    {
        case 0: return NOR+co1+"
                    ┏--------┓
                    ┃"NOR+co3+"●●●  "NOR+co1+"┃
                    ┃"NOR+co3+"●  ●  "NOR+co1+"┃
                    ┃"NOR+co3+"    ●  "NOR+co1+"┃
                    ┃"NOR+co3+"      ●"NOR+co1+"┃
                    ┗--------┛\n\n"NOR;

        case 1: return NOR+co1+"
                    ┏--------┓
                    ┃"NOR+co3+"●●●  "NOR+co1+"┃
                    ┃"NOR+co2+"●  "NOR+co3+"●  "NOR+co1+"┃
                    ┃"NOR+co3+"    ●  "NOR+co1+"┃
                    ┃"NOR+co3+"      ●"NOR+co1+"┃
                    ┗--------┛\n\n"NOR;

        case 2: return NOR+co1+"
                    ┏--------┓
                    ┃"NOR+co2+"●"NOR+co3+"●●  "NOR+co1+"┃
                    ┃"NOR+co2+"●  "NOR+co3+"●  "NOR+co1+"┃
                    ┃"NOR+co3+"    ●  "NOR+co1+"┃
                    ┃"NOR+co3+"      ●"NOR+co1+"┃
                    ┗--------┛\n\n"NOR;

        case 3: return NOR+co1+"
                    ┏--------┓
                    ┃"NOR+co2+"●●"NOR+co3+"●  "NOR+co1+"┃
                    ┃"NOR+co2+"●  "NOR+co3+"●  "NOR+co1+"┃
                    ┃"NOR+co3+"    ●  "NOR+co1+"┃
                    ┃"NOR+co3+"      ●"NOR+co1+"┃
                    ┗--------┛\n\n"NOR;

        case 4: return NOR+co1+"
                    ┏--------┓
                    ┃"NOR+co2+"●●●  "NOR+co1+"┃
                    ┃"NOR+co2+"●  "NOR+co3+"●  "NOR+co1+"┃
                    ┃"NOR+co3+"    ●  "NOR+co1+"┃
                    ┃"NOR+co3+"      ●"NOR+co1+"┃
                    ┗--------┛\n\n"NOR;

        case 5: return NOR+co1+"
                    ┏--------┓
                    ┃"NOR+co2+"●●●  "NOR+co1+"┃
                    ┃"NOR+co2+"●  ●  "NOR+co1+"┃
                    ┃"NOR+co3+"    ●  "NOR+co1+"┃
                    ┃"NOR+co3+"      ●"NOR+co1+"┃
                    ┗--------┛\n\n"NOR;

        case 6: return NOR+co1+"
                    ┏--------┓
                    ┃"NOR+co2+"●●●  "NOR+co1+"┃
                    ┃"NOR+co2+"●  ●  "NOR+co1+"┃
                    ┃"NOR+co2+"    ●  "NOR+co1+"┃
                    ┃"NOR+co3+"      ●"NOR+co1+"┃
                    ┗--------┛\n\n"NOR;

        case 7: return NOR+co1+"
                    ┏--------┓
                    ┃"NOR+co2+"●●●  "NOR+co1+"┃
                    ┃"NOR+co2+"●  ●  "NOR+co1+"┃
                    ┃"NOR+co2+"    ●  "NOR+co1+"┃
                    ┃"NOR+co2+"      ●"NOR+co1+"┃
                    ┗--------┛\n\n"NOR;
    }

    return "你的七星灯里还有八个灯亮着！！！！！！！真是太厉害了！！！\n";
}
