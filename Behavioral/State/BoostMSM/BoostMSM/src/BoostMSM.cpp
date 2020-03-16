#include <string>
#include <vector>
#include <iostream>
#include <boost/msm/back/state_machine.hpp>
#include <boost/msm/front/state_machine_def.hpp>
#include <boost/msm/front/functor_row.hpp>
using namespace std;
namespace msm = boost::msm;
namespace mpl = boost::mpl;
using namespace msm::front;

vector<string> state_names{
    "Off hook"s,
    "Connecting"s,
    "Connected"s,
    "On hold"s,
    "Destroyed"s
};

struct CallDialed {};
struct HungUp {};
struct CallConnected {};
struct PlacedOnHold {};
struct TakenOffHold {};
struct LeftMessage {};
struct PhoneThrownIntoWall {};

struct PhoneStateMachine : state_machine_def<PhoneStateMachine>
{
    struct OffHook : state<> {};
    struct Connecting : state<> {};
    struct Connected : state<> {};
    struct OnHold : state<> {};
    struct PhoneDestroyed : state<> {};

    struct transition_table : mpl::vector<
        Row<OffHook, CallDialed, Connecting>,
        Row<Connecting, CallConnected, Connected>,
        Row<Connected, PlacedOnHold, OnHold>,
        Row<OnHold, PhoneThrownIntoWall, PhoneDestroyed>
    > {};

    typedef OffHook initial_state;
};

int main()
{
    msm::back::state_machine<PhoneStateMachine> phone;

    auto info = [&]()
    {
        auto i = phone.current_state()[0];
        cout << "The phone is currently " << state_names[i] << "\n";
    };

    info();
    phone.process_event(CallDialed{});
    info();

    return 0;
}