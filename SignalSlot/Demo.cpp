#include "SignalSlot.hpp"

class SignalSlotTest : public Object {
public:
    Signal<> Signal0;
    Signal<int> Signal1;
    Signal<int, int> Signal2;
    Signal<int, int, int> Signal3;
    Signal<int, int, int, int> Signal4;
    Signal<int, int, int, int, int> Signal5;
    Signal<int, int, int, int, int, int> Signal6;
    Signal<int, int, int, int, int, int, int> Signal7;
    Signal<int, int, int, int, int, int, int, int> Signal8;

    // Error test: argsCount > 8
    //Signal<int, int, int, int, int, int, int, int, int> Signal9;
    // Error test: argsCount != sizeof...(Args)
    //SignalTemplate<1, int, int> SignalErrorArgs12;
    //SignalTemplate<1, int, int, int> SignalErrorArgs13;
    //SignalTemplate<1, int, int, int, int> SignalErrorArgs14;

    void Slot0()
    {
        printf("Slot0\r\n");
    }

    void Slot1(int d1)
    {
        printf("Slot1 %d\r\n", d1);
    }

    void Slot2(int d1, int d2)
    {
        printf("Slot2 %d %d\r\n", d1, d2);
    }

    void Slot3(int d1, int d2, int d3)
    {
        printf("Slot3 %d %d %d\r\n", d1, d2, d3);
    }

    void Slot4(int d1, int d2, int d3, int d4)
    {
        printf("Slot4 %d %d %d %d\r\n", d1, d2, d3, d4);
    }

    void Slot5(int d1, int d2, int d3, int d4, int d5)
    {
        printf("Slot5 %d %d %d %d %d\r\n", d1, d2, d3, d4, d5);
    }

    void Slot6(int d1, int d2, int d3, int d4, int d5, int d6)
    {
        printf("Slot6 %d %d %d %d %d %d\r\n", d1, d2, d3, d4, d5, d6);
    }

    void Slot7(int d1, int d2, int d3, int d4, int d5, int d6, int d7)
    {
        printf("Slot7 %d %d %d %d %d %d %d\r\n", d1, d2, d3, d4, d5, d6, d7);
    }

    void Slot8(int d1, int d2, int d3, int d4, int d5, int d6, int d7, int d8)
    {
        printf("Slot8 %d %d %d %d %d %d %d %d\r\n", d1, d2, d3, d4, d5, d6, d7, d8);
    }
};

// Error test: error class (declare class)
class ErrorTest {
public:
    Signal<int> Signal1;

    void Slot1(int d1)
    {
        printf("Slot1 %d\r\n", d1);
    }
};

int main()
{
    SignalSlotTest test;

    Connect(test.Signal0, &test, &SignalSlotTest::Slot0);
    Connect(test.Signal1, &test, &SignalSlotTest::Slot1);
    Connect(test.Signal2, &test, &SignalSlotTest::Slot2);
    Connect(test.Signal3, &test, &SignalSlotTest::Slot3);
    Connect(test.Signal4, &test, &SignalSlotTest::Slot4);
    Connect(test.Signal5, &test, &SignalSlotTest::Slot5);
    Connect(test.Signal6, &test, &SignalSlotTest::Slot6);
    Connect(test.Signal7, &test, &SignalSlotTest::Slot7);
    Connect(test.Signal8, &test, &SignalSlotTest::Slot8);
    Emit(test.Signal0);
    Emit(test.Signal1, 101);
    Emit(test.Signal2, 201, 202);
    Emit(test.Signal3, 301, 302, 303);
    Emit(test.Signal4, 401, 402, 403, 404);
    Emit(test.Signal5, 501, 502, 503, 504, 505);
    Emit(test.Signal6, 601, 602, 603, 604, 605, 606);
    Emit(test.Signal7, 701, 702, 703, 704, 705, 706, 707);
    Emit(test.Signal8, 801, 802, 803, 804, 805, 806, 807, 808);

    Disconnect(test.Signal5, &test);
    Disconnect(test.Signal6, &test);
    Disconnect(test.Signal7, &test);
    Disconnect(test.Signal8, &test);
    Emit(test.Signal0);
    Emit(test.Signal1, 1101);
    Emit(test.Signal2, 1201, 1202);
    Emit(test.Signal3, 1301, 1302, 1303);
    Emit(test.Signal4, 1401, 1402, 1403, 1404);
    Emit(test.Signal5, 1501, 1502, 1503, 1504, 1505);
    Emit(test.Signal6, 1601, 1602, 1603, 1604, 1605, 1606);
    Emit(test.Signal7, 1701, 1702, 1703, 1704, 1705, 1706, 1707);
    Emit(test.Signal8, 1801, 1802, 1803, 1804, 1805, 1806, 1807, 1808);

    Connect(test.Signal5, &test, &SignalSlotTest::Slot5);
    Connect(test.Signal6, &test, &SignalSlotTest::Slot6);
    Emit(test.Signal0);
    Emit(test.Signal1, 2101);
    Emit(test.Signal2, 2201, 2202);
    Emit(test.Signal3, 2301, 2302, 2303);
    Emit(test.Signal4, 2401, 2402, 2403, 2404);
    Emit(test.Signal5, 2501, 2502, 2503, 2504, 2505);
    Emit(test.Signal6, 2601, 2602, 2603, 2604, 2605, 2606);
    Emit(test.Signal7, 2701, 2702, 2703, 2704, 2705, 2706, 2707);
    Emit(test.Signal8, 2801, 2802, 2803, 2804, 2805, 2806, 2807, 2808);

    Disconnect(test.Signal6, &test);
    Emit(test.Signal0);
    Emit(test.Signal1, 3101);
    Emit(test.Signal2, 3201, 3202);
    Emit(test.Signal3, 3301, 3302, 3303);
    Emit(test.Signal4, 3401, 3402, 3403, 3404);
    Emit(test.Signal5, 3501, 3502, 3503, 3504, 3505);
    Emit(test.Signal6, 3601, 3602, 3603, 3604, 3605, 3606);
    Emit(test.Signal7, 3701, 3702, 3703, 3704, 3705, 3706, 3707);
    Emit(test.Signal8, 3801, 3802, 3803, 3804, 3805, 3806, 3807, 3808);

    // Error test: error class
    //ErrorTest errorTest;
    //Connect(errorTest.Signal1, &errorTest, &ErrorTest::Slot1);

    system("pause");
    return 0;
}
