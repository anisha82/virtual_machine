# Use an official C++ image as the base
FROM gcc:latest

# Set the working directory inside the container
WORKDIR /app

# Copy the source folder into the container
COPY src/ ./src

# Install dependencies (if needed)
RUN apt-get update && apt-get install -y build-essential

# Compile the program inside the src directory
RUN g++ -o virtual_machine ./src/main.cpp

# Set the default command to run your program
CMD ["./virtual_machine"]
