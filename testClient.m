% Script to test how the sockets work
shstate.n = 4;
shstate.dat = [1:4]*0.1;
N = 1000;

matlab_client('connect');
A = matlab_client('version');
fprintf('Server version %d\n', A.n);

% time:
tic;
for c1=1:N
    A = matlab_client('getsquares', shstate);
end
B = toc;
matlab_client('close')
fprintf('Mean time per call: %f microseconds.\n', 10^6*B/N);
