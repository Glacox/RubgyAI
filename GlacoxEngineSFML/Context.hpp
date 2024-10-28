#pragma once
namespace Context {
    enum class State {
        Idle,
        Moving,
        Attacking,
        HasBall,
        ChasingBall,
        PassingBall,
        Intercepting,
        Following
    };
};