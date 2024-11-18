# Use an official C++ image as the base
FROM gcc:latest

# Set the working directory inside the container
WORKDIR /app

# Copy the source folder and program file into the container
COPY src/ ./src
COPY program.vm ./program.vm

# Install dependencies (if needed)
RUN apt-get update && apt-get install -y build-essential && rm -rf /var/lib/apt/lists/*

# Compile the program inside the src directory
RUN g++ -o virtual_machine ./src/main.cpp

# Ensure the executable has the correct permissions
RUN chmod +x virtual_machine

# Optional: Debugging to check file paths
RUN ls -l /app

# Set the default command to run your program
ENTRYPOINT ["./virtual_machine"]
CMD ["program.vm"]
